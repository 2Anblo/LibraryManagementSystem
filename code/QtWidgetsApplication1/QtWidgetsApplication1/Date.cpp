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

void Date::setday(int d)   //���� ��
{
	day = d;
}

void Date::setmonth(int m)   //���� ��
{
	month = m;
}

void Date::setyear(int y)  //���� ��
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

Status Date::subday(Date now)          //1 ��ʾ���� 0��ʾ���ܻ����� 
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

Date Get_Sys_Time()  //���ص�ǰϵͳʱ��
{
	struct tm today;    //���ʱ��Ľṹ��
	time_t one;         //���ʱ������� 
	Date now;
	one = time(&one);      //���ϵͳʱ��
	today = *(gmtime(&one));
	now.setyear(today.tm_year - 100 + 2000);  //2011�귵��111
	now.setmonth(today.tm_mon + 1);     //9�·���8;
	now.setday(today.tm_mday);
	return now;
}
string Date::dateFormat() {
	string dateString = to_string(getyear()) + "��" + to_string(getmonth()) + "��" + to_string(getday()) + "��";
	return dateString;
}

bool isLeapYear(int year){
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// ��ȡĳ��ĳ�µ��������
int getDaysInMonth(int year, int month){
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(year) ? 29 : 28;
	default:
		return 30;  // Ĭ�Ϸ���30�죬��Ӧ������
	}
}

// ���رȵ�ǰ���ڴ�һ���µĳ�������
string Date::overdueFormat(){
	int newYear = year;
	int newMonth = month + 1;
	int newDay = day;

	// ����·ݳ���12�£�����ݼ�1�����·�����Ϊ1��
	if (newMonth > 12) {
		newMonth = 1;
		newYear += 1;
	}

	// �������·ݵ�������
	int daysInMonth = getDaysInMonth(newYear, newMonth);

	// �����ǰ���ڳ������¸��µ������������������Ϊ�������һ��
	if (newDay > daysInMonth) {
		newDay = daysInMonth;
	}

	return std::to_string(newYear) + "��" + std::to_string(newMonth) + "��" + std::to_string(newDay) + "��";

}
