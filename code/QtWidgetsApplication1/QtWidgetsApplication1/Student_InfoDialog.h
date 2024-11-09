#pragma once

#include <QDialog>
#include "ui_Student_InfoDialog.h"
#include "cell_personInfo.h"
#include "cell_return.h"
#include "cell_borrow.h"
#include "cell_recommend.h"
#include "Student.h"

class Student_InfoDialog : public QDialog
{
	Q_OBJECT

public:
	Student_InfoDialog(Student* m_stu, BookSet* m_book,SBList* m_borrow, QWidget *parent = nullptr);
	~Student_InfoDialog();
	// 初始化页面，设置各个子页面的初始状态
	void initPage();
public slots:
    // 处理菜单动作，根据用户的选择调整界面显示
	void dealMenu();
private:
	Ui::Student_InfoDialogClass ui;// 用户界面的设置，由 Qt 的 UIC 工具自动生成和管理
	// 学生借阅页面
	cell_borrow* m_borrowPage;
    // 学生归还页面
	cell_return* m_returnPage;
    // 学生个人信息页面
	cell_personInfo* m_personInfoPage;
    // 推荐书籍页面
	cell_recommend* m_recommendPage;
    // 指向当前操作的学生对象
	Student* stu;
    // 指向当前操作的书籍集合
	BookSet* book;
    // 指向当前借阅信息的链表集合
	SBList* borrow;   

};
