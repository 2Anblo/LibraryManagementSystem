# pragma once
# include "Date.h"
#include "PreDefination.h"


class BorrowInfo    //借阅信息
{
private:
	string bookno;    //书号
	Date borrowday;     //借阅日期
	
	string bookname;  //书名
public:
    // 设置书号
	void setbookno(string bno);
    // 设置借阅日期
	void setborrowday(Date d);
    // 获取书号
	string getbookno();
    // 获取借阅日期
	Date getborrowday();

	friend std::istream& operator>>(std::istream& is, BorrowInfo& bi);   //重载输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, BorrowInfo& bi);

    // 设置书名
	void setbookname(string bname);
    // 获取书名
	string getbookname();

};
