#pragma once

#include <QWidget>
#include <QtWidgets/QMainWindow>

#include "ui_Student_InfoWidget.h"

class Student_InfoWidget : public QWidget
{
	Q_OBJECT

public:
	Student_InfoWidget(QWidget* parent = nullptr);
	~Student_InfoWidget();

private:
	Ui::Student_InfoWidgetClass ui;
};
