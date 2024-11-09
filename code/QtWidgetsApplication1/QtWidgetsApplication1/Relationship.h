# pragma once
#include "PreDefination.h"

class Relationship
{
private:
	string stuno;    //学号 
	string bookno;    //书号 
	string stumobile;     //手机号 
public:
	void setstuno(string sno);

	void setbookno(string bno);

	void setstumobile(string mobi);

	string getstuno();

	string getbookno();

	string getstumobile();

	friend std::istream& operator>>(std::istream& is, Relationship& re);   //重载输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, Relationship& re);
};