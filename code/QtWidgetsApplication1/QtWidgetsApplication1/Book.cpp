# pragma once
#include "Book.h"

int index(string s1, string s2)    //原创 s2包含于s1中函数
{ //利用string.h函数中的strstr    解释strstr函数可以将前者包含后者的部分及以后的字符输出 如果不存在包含关系则为NULL 
	if (s1.find(s2) != s1.npos)
		return OK;
	else return ERROR;
}

void Book::setbookno(string no)
{
	bookno = no;
}

void Book::setbookname(string name)
{
	bookname = name;
}

void Book::setauthor(string au)
{
	author = au;
}

void Book::setpublisher(string pub)
{
	publisher = pub;
}

void Book::settotal(int i)
{
	totalnum = i;
}

void Book::setborrow(int i)
{
	borrownum = i;
}

void Book::setday(Date t)
{
	pubday = t;
}

string Book::getbookno()
{
	return bookno;
}

string Book::getbookname()
{
	return bookname;
}

string Book::getauthor()
{
	return author;
}

string Book::getpublisher()
{
	return publisher;
}

int Book::gettotalnum()
{
	return totalnum;
}

int Book::getborrownum()
{
	return borrownum;
}

Date& Book::getpubday()
{
	return pubday;
}

bool Book::operator == (Book b)
{
	if (this->bookno == b.getbookno())
		return true;
	else
		return false;
}

Status Book::index_bookno(string info)
{  //查询图书e书号是否包含info 
	if (index(bookno, info))return OK;
	return ERROR;
}
Status Book::index_author(string info)
{  //查询图书e作者是否包含info 
	if (index(author, info)) return OK;
	return ERROR;
}
Status Book::index_bookname(string info)
{  //查询图书e的名称中是否包含info 
	if (index(bookname, info)) return OK;
	return ERROR;
}
Status Book::index_publisher(string info)
{  //查询图书e的出版社是否包含info 
	if (index(publisher, info)) return OK;
	return ERROR;
}

std::istream& operator>>(std::istream& is, Book& boo)
{
	is >> boo.bookno;
	is >> boo.bookname;
	is >> boo.author;
	is >> boo.publisher;
	is >> boo.totalnum;
	is >> boo.borrownum;
	is >> boo.pubday;
	return is;
}
std::ostream& operator<<(std::ostream& os, Book& boo)
{
	os << boo.bookno << " ";
	os << boo.bookname << " ";
	os << boo.author << " ";
	os << boo.publisher << " ";
	os << boo.totalnum << " ";
	os << boo.borrownum << " ";
	os << boo.pubday << "\n";
	return os;
}
bool operator ==(Book& book1, Book& book2)
{
	return book1.bookno == book2.bookno;
}
std::string Book::toString() {
	return bookno + " " + bookname + " " + author + " " + publisher + " " +
		std::to_string(totalnum) + " " + std::to_string(borrownum) + " " +
		std::to_string(pubday.getyear()) + " " + std::to_string(pubday.getmonth()) + " " + std::to_string(pubday.getday());
}
