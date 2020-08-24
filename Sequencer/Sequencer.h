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
#pragma once

#include "qmainwindow.h"

#include "AboutDialog.h"
#include "RenderingThread.h"

#include "ui_Sequencer.h"

class Sequencer final : public QMainWindow
{
	Q_OBJECT

public:
	explicit Sequencer(QWidget* parent = Q_NULLPTR);
	~Sequencer();

public slots:
	// ReSharper disable once CppInconsistentNaming
	void on_actionOpen_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_textBrowser_textChanged();

	// ReSharper disable once CppInconsistentNaming
	void on_actionExample_File_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionCopy_Diagram_to_Clipboard_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionExport_Diagram_As_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionSave_As_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionAbout_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionGrammar_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionSave_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionAdd_Author_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionAdd_Title_triggered();

	// ReSharper disable once CppInconsistentNaming
	void on_actionAdd_Date_triggered();

	// update the UI with the new diagram
	void update_diagram(const QPixmap img);

private:
	Ui::SequencerClass ui;

	RenderingThread worker_thread_;

	void save_source_to_file(const std::string file_name);

	void replace_header_token(const std::string& token, const std::string& replacement);
	
};
