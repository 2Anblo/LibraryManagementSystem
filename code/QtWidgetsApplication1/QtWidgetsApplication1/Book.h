# pragma once
# include "Date.h"
#include "PreDefination.h"


int index(string s1, string s2);

class Book
{
private:
	string bookno;    	 //书号 
	string bookname;      //姓名 
	string author;    	 //作者 
	string publisher;      //出版社 
	int totalnum;			 //馆藏图书量 
	int borrownum;           //借出数量 
	Date pubday;             //出版日期 

public:
// 设置书号
	void setbookno(string no);
 // 设置书名
	void setbookname(string name);
 // 设置作者名
	void setauthor(string au);
// 设置出版社
	void setpublisher(string pub);
 // 设置馆藏总量
	void settotal(int i);
// 设置借出数量
	void setborrow(int i);
 // 设置出版日期
	void setday(Date t);
 // 获取书号
	string getbookno();
 // 获取书名
	string getbookname();
// 获取作者名
	string getauthor();
// 获取出版社名称
	string getpublisher();
// 获取馆藏总量
	int gettotalnum();
// 获取借出数量
	int getborrownum();
// 获取出版日期
	Date& getpubday();
 // 重载相等运算符，比较两本书是否相等
	bool operator == (Book b);
 // 查找与指定书号匹配的书籍
	Status index_bookno(string info);
	 // 查找与指定作者匹配的书籍
	Status index_author(string info)
		;
		 // 查找与指定书名匹配的书籍
	Status index_bookname(string info);
	 // 查找与指定出版社匹配的书籍
	Status index_publisher(string info);

	friend std::istream& operator>>(std::istream& is, Book& boo);   //重载输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, Book& boo);	 // 重载输出运算符，用于向输出流写入书籍信息
	friend bool operator ==(Book& book1, Book& book2);	// 重载全局相等运算符，用于比较两本书是否完全相同
 // 将书籍信息转化为字符串形式
	std::string toString();

};
