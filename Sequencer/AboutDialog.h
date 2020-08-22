#pragma once

#include <QWidget>
#include "ui_AboutDialog.h"

class AboutDialog : public QWidget
{
	Q_OBJECT

public:
	AboutDialog(QWidget *parent = Q_NULLPTR);
	~AboutDialog();

private:
	Ui::AboutDialog ui;
};
