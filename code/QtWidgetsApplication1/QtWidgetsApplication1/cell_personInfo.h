#pragma once

#include <QWidget>
#include "ui_cell_personInfo.h"
#include "Student.h"
#include <QRandomGenerator>
class cell_personInfo : public QWidget
{
	Q_OBJECT

public:
	cell_personInfo(Student* m_stu, QWidget *parent = nullptr);
	~cell_personInfo();

private:
	Ui::cell_personInfoClass ui;
	Student* stu;
};
