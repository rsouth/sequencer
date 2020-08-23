#include "Sequencer.h"
//#include "AboutDialog.h"

#include <QtWidgets/qfiledialog.h>
#include "qclipboard.h"

#include "RenderableDiagram.h"
#include "RenderingJob.h"

using namespace cimg_library;

Sequencer::Sequencer(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.splitter->setStretchFactor(0, 1);
	ui.splitter->setStretchFactor(1, 20);

	connect(&this->worker_thread_, &RenderingThread::render_completed, this, &Sequencer::update_ui);
}

Sequencer::~Sequencer()
{
	disconnect(&this->worker_thread_, &RenderingThread::render_completed, this, &Sequencer::update_ui);

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
		std::list<std::string> lines;
		QTextStream in(&input_file);
		while (!in.atEnd())
		{
			auto line = in.readLine();
			lines.push_back(line.toStdString());
		}
		input_file.close();

		// concat the lines
		const auto joinedLines = std::accumulate(
			std::next(lines.begin()),
			lines.end(),
			lines.front(),
			[](std::string a, std::string b)
			{
				return a + "\n" + b;
			}
		);

		// give lines to the textArea
		// auto* object = findChild<QTextBrowser*>("textBrowser");
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
		"Server -> Service: Query\n"
		"Service --> Server: Data\n"
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
	this->save_to_file(file_name.toStdString());
}

void Sequencer::on_actionAbout_triggered()
{
	AboutDialog* about_dialog = new AboutDialog();
	about_dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinimizeButtonHint);
	about_dialog->setAttribute(Qt::WA_DeleteOnClose);
	about_dialog->show();
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
		this->save_to_file(document_title.toStdString());
	}
}

void Sequencer::save_to_file(const std::string file_name)
{
	QFile output_file(file_name.c_str());
	if (output_file.open(QIODevice::WriteOnly))
	{
		// get lines from txt box as string
		auto text = this->ui.textBrowser->toPlainText();

		// std::list<std::string> lines;
		QTextStream out(&output_file);
		out << text;
		output_file.close();

		this->ui.textBrowser->setDocumentTitle(file_name.c_str());

	}
	else
	{
		// pop up some error msg?
	}
}


// slot: update_ui
void Sequencer::update_ui(const QPixmap img)
{
	ui.label->setPixmap(img);
	ui.label->setFixedSize(img.width(), img.height());
	QApplication::processEvents();
}
