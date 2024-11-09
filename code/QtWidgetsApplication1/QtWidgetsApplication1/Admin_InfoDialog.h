#pragma once

#include <QDialog>
#include "ui_Admin_InfoDialog.h"
#include "BookSet.h"
#include "StudentSet.h"

class Admin_InfoDialog : public QDialog
{
	Q_OBJECT

public:
	Admin_InfoDialog(QWidget* parent = nullptr);
	~Admin_InfoDialog();
	void set_TabelWghit();    // 设置图书表格的界面元素

	void set_TabelWghit_stu();    // 设置学生表格的界面元素

	std::vector<QPushButton*> btn; //表格上的控件
	std::vector<QCheckBox*> mark; //表格上的选中标记

	std::vector<QPushButton*> stu_btn;    // 存储学生表格中的按钮

	std::vector<QCheckBox*>stu_mark;    // 存储学生表格中的复选框

	void refreshTable(BookSet* set);    // 刷新书籍信息表格，显示给定的书籍集

	void exchange_Set(const string str);
	int find_book_and_return_idx(Book* book);    // 在书籍集中查找指定书籍并返回其索引

	int find_stu_and_return_idx(Student* stu);    // 在学生集中查找指定学生并返回其索引

	//安全性验证
	bool requireInt(const QString& str);// 验证字符串是否为整数
	bool isValidDateFormat(const QString& Qstr);// 验证日期格式是否有效
	string getSafeString(const QTableWidgetItem* item);// 从表项中获取安全字符串
	bool isNumber(string str);// 检查字符串是否全部为数字
	bool isBooknoUnique(int i, QTableWidgetItem* item);// 检查书号是否唯一
	bool isStunoUnique(int i, QTableWidgetItem* item);// 检查学号是否唯一
public slots:
    // 设置当前页面
	void set_page(int page_name);
    // 添加项目到书籍表格
	void add_item_to_TableWghit();
    // 从表格获取书籍对象
	Book* get_book_from_TableWghit(int i);
    // 保存或更改表格中的项目
	void save_or_change_for_TableWghit(int i);
    // 从书籍表格删除项目
	void delete_book_from_TableWghit();
    // 取消书籍表格中的选定项目
	void cancel_item_from_TableWghit();
    // 全选或取消选择所有项目
	void choise_or_unchoise_all_item_from_TableWghit();
    // 从文件添加书籍
	void add_book_from_file();

    // 执行书籍搜索操作
	void onSearchAction_book();
    // 执行学生搜索操作
	void onSearchAction_stu();

    // 刷新学生信息表格
	void refreshTable_stu(StudentSet* s_set);
    // 添加项目到学生表格
	void add_item_to_stu_TableWghit();
    // 保存或更改学生表格中的项目
	void save_or_change_for_stu_TableWghit(int i);
    // 从学生表格删除项目
	void delete_book_from_stu_TableWghit();
    // 全选或取消选择所有学生表格项目
	void choise_or_unchoise_all_item_from_stu_TableWghit();
    // 从学生表格获取学生对象
	Student* get_student_from_stu_TableWghit(int i);
    // 从文件添加学生
	void add_stu_from_file();

    // 显示自定义消息框
	void showCustomMessageBox(const std::string& title, const std::string& message);
private:
	Ui::Admin_InfoDialogClass ui;// 管理员界面对象
	BookSet* b_set;// 主书籍集
	StudentSet* s_set;// 主学生集
	BookSet* search_BookSet;  // 搜索结果书籍集
	StudentSet* search_StuSet;  // 搜索结果学生集

	BookSet* current_BookSet;  // 当前活动的书籍集
	StudentSet* current_StuSet;  // 当前活动的学生集

};
