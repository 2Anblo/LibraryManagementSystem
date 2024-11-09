# pragma once
# include "Student.h"

int index(string s1, string s2, int a)    //ԭ�� s2������s1�к���
{ //����string.h�����е�strstr    ����strstr�������Խ�ǰ�߰������ߵĲ��ּ��Ժ���ַ���� ��������ڰ�����ϵ��ΪNULL 
	if (s1.find(s2) != s1.npos)
		return OK;
	else return ERROR;
}

void Student::setstuno(string no)  //����ѧ��
{
	studentno = no;
}

void Student::setstuname(string name)  //��������
{
	studentname = name;
}

void Student::setstumajor(string major)  //����רҵ
{
	studentmajor = major;
}

void Student::setstuclass(string c) //���ð༶
{
	studentclass = c;
}

void Student::setstumobi(string mobi)  //�����ֻ���
{
	studentmobile = mobi;
}

string Student::getstuno()   //��ȡѧ��
{
	return studentno;
}

string Student::getstuname()   //��ȡ����
{
	return studentname;
}

string Student::getstumajor()  //��ȡרҵ
{
	return studentmajor;
}

string Student::getstuclass()   //��ȡ�༶
{
	return studentclass;
}

string Student::getstumobi()  //��ȡ�ֻ���
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
{   //��ѯѧ��e��ѧ���Ƿ����info��
	if (index(studentno, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stuname(string info)
{  //��ѯѧ��e�������Ƿ����info
	if (index(studentname, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stumajor(string info)
{  //��ѯѧ��e��רҵ�Ƿ����info
	if (index(studentmajor, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stuclass(string info)
{  //��ѯѧ��e�İ༶�Ƿ����info
	if (index(studentclass, info, 1)) return OK;
	return ERROR;
}
Status Student::index_stumobile(string info)
{  //��ѯѧ��e���ֻ��Ƿ����info
	if (index(studentmobile, info, 1)) return OK;
	return ERROR;
}

Status Student::equal_stuno(Student b)     //�Ƚ�ѧ��ѧ���Ƿ���ͬ 
{
	if (studentno == b.getstuno())
		return TRUE;
	else
		return FALSE;
}

Status Student::equal_stuma_or_cl(Student b)     //�Ƚ�ѧ����רҵ��༶�Ƿ���ͬ 
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