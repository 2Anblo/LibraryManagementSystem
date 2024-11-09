#pragma once
#include "PreDefination.h"
//日期
class Date
{
private:
	int day, month, year;

public:

	Date(int day, int month, int year) :day(0), month(0), year(0) {}
	Date() :day(0), month(0), year(0) {}
	Date(string str) {
		string dateString = "2013年7月16日";
		// 提取年份
		size_t yearPos = dateString.find("年");
		this->year = std::stoi(dateString.substr(0, yearPos));

		// 提取月份
		size_t monthPos = dateString.find("月");
		this->month = std::stoi(dateString.substr(yearPos + 2, monthPos));

		// 提取日期
		size_t dayPos = dateString.find("日");
		this->day = std::stoi(dateString.substr(monthPos + 2, dayPos));
	}

	friend std::istream& operator>>(std::istream& is, Date& d);   //重载输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, Date& d);

	void setday(int d);   //设置 日


	void setmonth(int m);   //设置 月


	void setyear(int y);  //设置 年


	int getday();

	int getmonth();

	int getyear();

	Status subday(Date now);          //1 表示超期 0表示还能缓几天 

	string dateFormat();

	string overdueFormat();
};
int totalday(int year, int month, int day);
Date Get_Sys_Time();