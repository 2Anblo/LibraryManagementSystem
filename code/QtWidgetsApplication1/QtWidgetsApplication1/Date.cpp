# include "Date.h"

int totalday(int year, int month, int day)
{
	int i = 0;
	switch (month - 1)
	{
	case 11: i += 30;
	case 10: i += 31;
	case 9: i += 30;
	case 8: i += 31;
	case 7: i += 31;
	case 6: i += 30;
	case 5: i += 31;
	case 4: i += 30;
	case 3: i += 31;
	case 2: if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))   i += 29;
		  else   i += 28;
	case 1: i += 31;
	}
	i += day; return i;
}

void Date::setday(int d)   //设置 日
{
	day = d;
}

void Date::setmonth(int m)   //设置 月
{
	month = m;
}

void Date::setyear(int y)  //设置 年
{
	year = y;
}

int Date::getday()
{
	return day;
}

int Date::getmonth()
{
	return month;
}

int Date::getyear()
{
	return year;
}

Status Date::subday(Date now)          //1 表示超期 0表示还能缓几天 
{
	if (now.getyear() - year > 1) return 1;
	if (now.getyear() == year)
	{
		if (totalday(now.getyear(), now.getmonth(), now.getday()) - totalday(year, month, day) > 30) return 1;
	}
	if (now.getyear() - year == 1)
	{
		if (totalday(now.getyear(), now.getmonth(), now.getday()) + (365 - totalday(year, month, day)) > 30) return 1;
	}
	return 0;
}

std::istream& operator>>(std::istream& is, Date& d)
{
	is >> d.year;
	is >> d.month;
	is >> d.day;
	return is;
}
std::ostream& operator<<(std::ostream& os, Date& d)
{
	os << d.year << " ";
	os << d.month << " ";
	os << d.day;
	return os;
}

Date Get_Sys_Time()  //返回当前系统时间
{
	struct tm today;    //存放时间的结构体
	time_t one;         //存放时间的类型 
	Date now;
	one = time(&one);      //获得系统时间
	today = *(gmtime(&one));
	now.setyear(today.tm_year - 100 + 2000);  //2011年返回111
	now.setmonth(today.tm_mon + 1);     //9月返回8;
	now.setday(today.tm_mday);
	return now;
}
string Date::dateFormat() {
	string dateString = to_string(getyear()) + "年" + to_string(getmonth()) + "月" + to_string(getday()) + "日";
	return dateString;
}

bool isLeapYear(int year){
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取某年某月的最大天数
int getDaysInMonth(int year, int month){
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(year) ? 29 : 28;
	default:
		return 30;  // 默认返回30天，不应到这里
	}
}

// 返回比当前日期大一个月的超期日期
string Date::overdueFormat(){
	int newYear = year;
	int newMonth = month + 1;
	int newDay = day;

	// 如果月份超过12月，则年份加1并将月份设置为1月
	if (newMonth > 12) {
		newMonth = 1;
		newYear += 1;
	}

	// 根据新月份调整天数
	int daysInMonth = getDaysInMonth(newYear, newMonth);

	// 如果当前日期超出了下个月的最大天数，则将日期设为该月最后一天
	if (newDay > daysInMonth) {
		newDay = daysInMonth;
	}

	return std::to_string(newYear) + "年" + std::to_string(newMonth) + "月" + std::to_string(newDay) + "日";

}
