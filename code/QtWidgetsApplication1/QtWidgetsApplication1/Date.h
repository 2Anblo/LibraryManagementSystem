#pragma once
#include "PreDefination.h"
//����
class Date
{
private:
	int day, month, year;

public:

	Date(int day, int month, int year) :day(0), month(0), year(0) {}
	Date() :day(0), month(0), year(0) {}
	Date(string str) {
		string dateString = "2013��7��16��";
		// ��ȡ���
		size_t yearPos = dateString.find("��");
		this->year = std::stoi(dateString.substr(0, yearPos));

		// ��ȡ�·�
		size_t monthPos = dateString.find("��");
		this->month = std::stoi(dateString.substr(yearPos + 2, monthPos));

		// ��ȡ����
		size_t dayPos = dateString.find("��");
		this->day = std::stoi(dateString.substr(monthPos + 2, dayPos));
	}

	friend std::istream& operator>>(std::istream& is, Date& d);   //����������������
	friend std::ostream& operator<<(std::ostream& os, Date& d);

	void setday(int d);   //���� ��


	void setmonth(int m);   //���� ��


	void setyear(int y);  //���� ��


	int getday();

	int getmonth();

	int getyear();

	Status subday(Date now);          //1 ��ʾ���� 0��ʾ���ܻ����� 

	string dateFormat();

	string overdueFormat();
};
int totalday(int year, int month, int day);
Date Get_Sys_Time();