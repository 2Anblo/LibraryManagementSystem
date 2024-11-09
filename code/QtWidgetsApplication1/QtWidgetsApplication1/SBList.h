#pragma once
# include "StudentNodeSet.h"
#include "PreDefination.h"


class SBList
{
private:
	int studentnum;             //借阅书籍的人数 
	int borrownum;              //借出去的书总数 
	StudentNodeSet sblist;    //学生借阅表 
public:
    // 开始一个新的借阅流程

	Status begin_borrow();
    // 打开并加载借阅列表，通常从文件中读取

	Status OpenBorrowList();
    // 将当前的借阅信息写入到文件中

	Status WriteToFile();
    // 检查指定学生是否已在借阅列表中

	int StuWhetherIn(string no);

    // 向借阅列表中添加一个新的学生节点
	void pushelem(StudentNode sn);

    // 设置当前借阅书籍的人数
	void setstudentnum(int s);

    // 设置借出去的书籍总数
	void setborrownum(int b);

    // 获取当前借阅书籍的人数
	int getstudentnum();

    // 获取借出去的书籍总数
	int getborrownum();

    // 获取指定学生的个人借阅书籍数量
	int getpersonalnum(string no);

    // 检查指定书籍是否已被指定学生借阅
	int BookWhetherIn(string sn, string bn);

    // 为指定学生添加一个新的借阅关系
	void addanewrelation(string sn, BorrowInfo bi);

    // 学生归还一本书
	void returnbook(string sn, string bn);

    // 打印指定学生的所有借阅信息
	void printbookinfo(string sn);

    // 打印单一书籍的借阅信息
	void printsinglebookinfo(string bn);

    // 更新借阅列表中的逾期书籍信息
	void outdate(Date now, StudentSet stu);

    // 获取学生借阅节点集
	StudentNodeSet getSBList();

    // 检查指定学生的借书限制是否达到上限
	bool bookLimit(string sn);

};