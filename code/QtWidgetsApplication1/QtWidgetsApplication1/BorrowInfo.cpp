# include "BorrowInfo.h"

void BorrowInfo::setbookno(string bno)
{
	bookno = bno;
}

void BorrowInfo::setborrowday(Date d)
{
	borrowday = d;
}

string BorrowInfo::getbookno()
{
	return bookno;
}

Date BorrowInfo::getborrowday()
{
	return borrowday;
}

std::istream& operator>>(std::istream& is, BorrowInfo& bi)
{
	is >> bi.bookno;

	is >> bi.bookname;

	is >> bi.borrowday;
	return is;
}
std::ostream& operator<<(std::ostream& os, BorrowInfo& bi)
{
	os << bi.bookno << " ";

	os << bi.bookname << " ";

	os << bi.borrowday;
	return os;
}

void BorrowInfo::setbookname(string bname) {
	bookname = bname;
}

string BorrowInfo::getbookname() {
	return bookname;
}