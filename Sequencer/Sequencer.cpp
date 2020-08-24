/*
 *     Copyright (C) 2020 rsouth (https://github.com/rsouth)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "Sequencer.h"

#include "qfiledialog.h"
#include "qclipboard.h"
#include "qdesktopservices.h"
#include "qinputdialog.h"

#include "RenderableDiagram.h"
#include "RenderingJob.h"
#include "StringUtils.h"

using namespace cimg_library;

Sequencer::Sequencer(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.splitter->setStretchFactor(0, 1);
	ui.splitter->setStretchFactor(1, 20);

	connect(&this->worker_thread_, &RenderingThread::render_completed, this, &Sequencer::update_diagram);
}

Sequencer::~Sequencer()
{
	disconnect(&this->worker_thread_, &RenderingThread::render_completed, this, &Sequencer::update_diagram);

	this->worker_thread_.requestInterruption();
	if (!this->worker_thread_.wait(100))
	{
		this->worker_thread_.terminate();
	}
}

void Sequencer::on_actionOpen_triggered()
{
	const auto file_name = QFileDialog::getOpenFileName(this, tr("Open File"), nullptr, tr("Sequencer Files (*.seq)"));
	QFile input_file(file_name);
	if (input_file.open(QIODevice::ReadOnly))
	{
		std::vector<std::string> lines;
		QTextStream in(&input_file);
		while (!in.atEnd())
		{
			auto line = in.readLine();
			lines.push_back(line.toStdString());
		}
		input_file.close();

		// concat the lines
		const auto joinedLines = StringUtils::join(lines, "\n");

		// give lines to the textArea
		this->ui.textBrowser->setText(QString(joinedLines.c_str()));
		this->ui.textBrowser->setDocumentTitle(file_name);
	}
}

void Sequencer::on_textBrowser_textChanged()
{
	const auto input_text = ui.textBrowser->toPlainText().toStdString();
	const auto rendering_job = RenderingJob(this->parent(), input_text);
	this->worker_thread_.render(rendering_job);
}

void Sequencer::on_actionExample_File_triggered()
{
	const auto text =
		"# metadata\n"
		":title Example Sequence Diagram\n"
		":author Mr. Sequence Diagram\n"
		":date\n"
		"\n"
		"# diagram\n"
		"Client -> Server: Request\n"
		"Server -> Server: Parses request\n"
		"Server ->> Service: Query\n"
		"Service -->> Server: Data\n"
		"Server --> Client: Response\n";
	
	this->ui.textBrowser->setText(text);
}

void Sequencer::on_actionCopy_Diagram_to_Clipboard_triggered()
{
	const QPixmap pixmap = this->ui.label->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
	if (!pixmap.isNull())
	{
		QImage image(pixmap.toImage());
		QClipboard* clipboard = QApplication::clipboard();
		if (clipboard && !image.isNull()) {
			clipboard->setImage(image, QClipboard::Mode::Clipboard);
		}
	}
}

void Sequencer::on_actionExport_Diagram_As_triggered()
{
	QString file_name = QFileDialog::getSaveFileName(this, tr("Export File"), nullptr, tr("Portable Network Graphics (PNG) (*.png)"));
	QPixmap pic = this->ui.label->pixmap(Qt::ReturnByValueConstant::ReturnByValue);
	pic.save(file_name, "PNG");
}

void Sequencer::on_actionSave_As_triggered()
{
	QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), nullptr, tr("Sequencer Files (*.seq)"));
	this->save_source_to_file(file_name.toStdString());
}

void Sequencer::on_actionAbout_triggered()
{
	AboutDialog* about_dialog = new AboutDialog();
	about_dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinimizeButtonHint);
	about_dialog->setAttribute(Qt::WA_DeleteOnClose);
	about_dialog->show();
}

void Sequencer::on_actionGrammar_triggered()
{
	QDesktopServices::openUrl(QUrl(QString("https://github.com/rsouth/sequencer/wiki/Grammar")));
}

void Sequencer::on_actionSave_triggered()
{
	QString document_title = this->ui.textBrowser->documentTitle();
	if (document_title.isEmpty())
	{
		this->on_actionSave_As_triggered();
	}
	else
	{
		this->save_source_to_file(document_title.toStdString());
	}
}

void Sequencer::save_source_to_file(const std::string file_name)
{
	QFile output_file(file_name.c_str());
	if (output_file.open(QIODevice::WriteOnly))
	{
		// get source text from UI
		auto text = this->ui.textBrowser->toPlainText();

		// write out to the file
		QTextStream out(&output_file);
		out << text;
		output_file.close();

		// update the document's title with the file name
		this->ui.textBrowser->setDocumentTitle(file_name.c_str());
	}
}

void Sequencer::on_actionAdd_Author_triggered()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Author Name"),
		tr("Author name:"), QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty())
	{
		replace_header_token(":author ", text.toStdString());
	}
}

void Sequencer::on_actionAdd_Title_triggered()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Diagram Title"), tr("Diagram title:"), QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty()) {
		replace_header_token(":title ", text.toStdString());
	}
}

void Sequencer::on_actionAdd_Date_triggered()
{
	replace_header_token(":date", "");
}

void Sequencer::replace_header_token(const std::string& token, const std::string& replacement)
{
	// get source text from the UI
	auto text = this->ui.textBrowser->toPlainText();
	auto lines = StringUtils::split(text.toStdString(), "\n");
	
	// add or replace the token line, using replacement as the value
	StringUtils::replace_token_and_value(lines, token, replacement);

	// join the lines back to a string and push back to the UI
	const auto joinedLines = StringUtils::join(lines, "\n");
	this->ui.textBrowser->setText(QString(joinedLines.c_str()));
}


// slot: update_diagram
// updates the UI with the new QPixmap holding the diagram
void Sequencer::update_diagram(const QPixmap img)
{
	ui.label->setPixmap(img);
	ui.label->setFixedSize(img.width(), img.height());
	QApplication::processEvents();
}
