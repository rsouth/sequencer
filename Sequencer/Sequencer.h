#pragma once


//#include <qmainwindow.h>

#include <QtWidgets/qmainwindow.h>

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
	void on_actionSave_triggered();

	void update_ui(const QPixmap img);

private:
	Ui::SequencerClass ui;

	RenderingThread worker_thread_;

	void save_to_file(const std::string file_name);
	
};
