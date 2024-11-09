#pragma once

#include <QWidget>
#include <QPoint>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include "ui_cell_borrow.h"
#include "BookSet.h"
#include "SBList.h"
#include "BorrowInfo.h"


class cell_borrow : public QWidget
{
	Q_OBJECT

public:
	cell_borrow(Student* stu, BookSet* set,SBList* borrow, QWidget *parent = nullptr);
	~cell_borrow();
	// 初始化借阅表格的设置，如列头、布局等
	void borrowTableSetting();
    // 刷新借阅表格，显示给定的书籍集
	void refreshTable(BookSet* set);
	

public slots:
    // 右键点击表格时显示菜单
	void onRightClickShowMenu(QPoint pos);
	// 处理借书动作，根据书籍ID处理借书逻辑
	void onBorrowBookAction(const QString& m_BID);
	// 执行搜索动作，根据用户输入更新表格显示
	void onSearchAction();
	// 更新时间，可能用于刷新界面或处理超时
	void updateTime();

private:
	BookSet* b_set;	// 存储与当前操作相关的书籍集合
	SBList* b_borrow;  // 存储与当前操作相关的借阅信息集合
	Student* b_stu;  // 指向当前操作的学生对象
	Ui::cell_borrowClass ui;  // 用户界面的设置，由 Qt 的 UIC 工具自动生成和管理
	QTimer* timer;  // 计时器，用于周期性执行 updateTime
};
