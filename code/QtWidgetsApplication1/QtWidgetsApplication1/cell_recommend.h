#pragma once

#include <QWidget>
#include "ui_cell_recommend.h"
#include "SBList.h"
#include <QMenu>
#include <QPoint>
#include "BookSet.h"
#include <QMessageBox>

class cell_recommend : public QWidget
{
	Q_OBJECT

public:
	cell_recommend(SBList* list, BookSet* set, QWidget *parent = nullptr);
	~cell_recommend();
	void recommendTableSetting();
	void refreshTable();
private:
	Ui::cell_recommendClass ui;
	SBList* r_list;
	BookSet* b_set;
};
