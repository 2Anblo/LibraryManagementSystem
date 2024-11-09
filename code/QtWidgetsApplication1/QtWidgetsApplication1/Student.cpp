# pragma once
# include "Student.h"

int index(string s1, string s2, int a)    //原创 s2包含于s1中函数
{ //利用string.h函数中的strstr    解释strstr函数可以将前者包含后者的部分及以后的字符输出 如果不存在包含关系则为NULL 
	if (s1.find(s2) != s1.npos)
		return OK;
	else return ERROR;
}

void Student::setstuno(string no)  //设置学号
{
	studentno = no;
}

void Student::setstuname(string name)  //设置姓名
{
	studentname = name;
}

void Student::setstumajor(string major)  //设置专业
{
	studentmajor = major;
}

void Student::setstuclass(string c) //设置班级
{
	studentclass = c;
}

void Student::setstumobi(string mobi)  //设置手机号
{
	studentmobile = mobi;
}

string Student::getstuno()   //获取学号
{
	return studentno;
}

string Student::getstuname()   //获取姓名
{
	return studentname;
}

string Student::getstumajor()  //获取专业
{
	return studentmajor;
}

string Student::getstuclass()   //获取班级
{
	return studentclass;
}

string Student::getstumobi()  //获取手机号
{
	return studentmobile;
}

bool Student::operator == (Student s)
{
	if (this->studentno == s.getstuno())
		return true;
	else
		return false;
}

Status Student::index_stuno(string info)
{   //查询学生e的学号是否符合info段
	if (index(studentno, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stuname(string info)
{  //查询学生e的姓名是否包含info
	if (index(studentname, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stumajor(string info)
{  //查询学生e的专业是否包含info
	if (index(studentmajor, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stuclass(string info)
{  //查询学生e的班级是否包含info
	if (index(studentclass, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stumobile(string info)
{  //查询学生e的手机是否包含info
	if (index(studentmobile, info, 1)) return OK;
	return ERROR;
}

Status Student::equal_stuno(Student b)     //比较学生学号是否相同 
{
	if (studentno == b.getstuno())
		return TRUE;
	else
		return FALSE;
}

Status Student::equal_stuma_or_cl(Student b)     //比较学生的专业或班级是否相同 
{
	if (studentmajor == b.getstumajor() || studentclass == b.getstuclass())
		return TRUE;
	return FALSE;
}

std::istream& operator>>(std::istream& is, Student& stu)
{
	is >> stu.studentno;
	is >> stu.studentname;
	is >> stu.studentmajor;
	is >> stu.studentclass;
	is >> stu.studentmobile;
	return is;
}
std::ostream& operator<<(std::ostream& os, Student& stu)
{
	os << stu.studentno << " ";
	os << stu.studentname << " ";
	os << stu.studentmajor << " ";
	os << stu.studentclass << " ";
	os << stu.studentmobile << "\n";
	return os;
}


std::string Student::toString() {
	return studentno + " " + studentname + " " + studentmajor + " " + studentclass+" "+studentmobile;
}

Student::Student(Student* stu) {
	this->studentno = stu->studentno;
	this->studentname = stu->studentname;
	this->studentclass = stu->studentclass;
	this->studentmajor = stu->studentmajor;
	this->studentmobile = stu->studentmobile;
}