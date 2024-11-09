# include "Relationship.h"


void Relationship::setstuno(string sno)
{
	stuno = sno;
}

void Relationship::setbookno(string bno)
{
	bookno = bno;
}

void Relationship::setstumobile(string mobi)
{
	stumobile = mobi;
}

string Relationship::getstuno()
{
	return stuno;
}

string Relationship::getbookno()
{
	return bookno;
}

string Relationship::getstumobile()
{
	return stumobile;
}

std::istream& operator>>(std::istream& is, Relationship& re)
{
	is >> re.stuno;
	is >> re.bookno;
	is >> re.stumobile;
	return is;
}
std::ostream& operator<<(std::ostream& os, Relationship& re)
{
	os << re.stuno << " ";
	os << re.bookno << " ";
	os << re.stumobile << "\n";
	return os;
}
