#pragma once

#include <QWidget>
#include <QScrollBar>
#include "ui_cell_return.h"
#include "SBList.h"
#include <QTimer>
#include <QMenu>
#include <QPoint>
#include "BookSet.h"
#include <QMessageBox>
#include <QStringList>

class cell_return : public QWidget
{
	Q_OBJECT

public:
	cell_return(Student* m_stu, SBList* list, BookSet* set, QWidget *parent = nullptr);
	~cell_return();

    // 初始化归还表格的设置，如列头、布局等
	void returnTableSetting();
    // 刷新归还表格，显示当前的借阅信息
	void refreshTable();
    // 设置和管理图片轮播
	void imageCarousel();

public slots:
    // 处理归还书籍动作，根据书籍ID处理归还逻辑
	void onReturnBookAction(const QString& m_BID);
    // 右键点击表格时显示菜单
	void onRightClickShowMenu(QPoint pos);
    // 显示下一张图片的轮播功能
	void nextImage(); 

private:
	Ui::cell_returnClass ui;	// 用户界面的设置，由 Qt 的 UIC 工具自动生成和管理
	QTimer* timer;	// 计时器，用于周期性执行 nextImage
	SBList* r_list;  // 存储与当前操作相关的借阅信息集合
	Student* r_stu;  // 指向当前操作的学生对象
	BookSet* b_set;  // 存储与当前操作相关的书籍集合
	QStringList imageList;  // 存储图片路径的列表
	int currentImageIndex;  // 当前显示的图片索引
};
