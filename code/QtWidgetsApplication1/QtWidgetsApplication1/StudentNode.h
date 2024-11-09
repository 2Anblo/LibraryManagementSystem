# pragma once
# include "PreDefination.h"
# include "BorrowInfoSet.h"
# include "StudentSet.h"


class StudentNode
{
private:
	string studentno;    //学号
	int borrownum;      //借阅数量
	BorrowInfoSet bilist;
public:
	void setstudentno(string no);

	void setborrownum(int b);

	void pushbook(BorrowInfo b);

	string getstudentno();

	int getborrownum();

	int BookWhetherIn(string bn);

	void returnbook(string bn);

	void printallbookinfo();

	void printsinglebookinfo(string bn);

	void outdate(Date now, StudentSet stu);

	BorrowInfoSet& getblist();

	friend std::istream& operator>>(std::istream& is, StudentNode& sn);   //重载输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, StudentNode& sn);
};