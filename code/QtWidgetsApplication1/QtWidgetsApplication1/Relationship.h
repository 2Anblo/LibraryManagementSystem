# pragma once
#include "PreDefination.h"

class Relationship
{
private:
	string stuno;    //ѧ�� 
	string bookno;    //��� 
	string stumobile;     //�ֻ��� 
public:
	void setstuno(string sno);

	void setbookno(string bno);

	void setstumobile(string mobi);

	string getstuno();

	string getbookno();

	string getstumobile();

	friend std::istream& operator>>(std::istream& is, Relationship& re);   //����������������
	friend std::ostream& operator<<(std::ostream& os, Relationship& re);
};