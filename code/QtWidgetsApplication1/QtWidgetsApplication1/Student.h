# pragma once
# include "PreDefination.h"

int index(string s1, string s2, int a);

class Student
{
private:
	string studentno;      //学号 
	string studentname;    //姓名 
	string studentmajor;   //专业 
	string studentclass;   //班级 
	string studentmobile;  //手机 

public:
// 默认构造函数

	Student() {};
    // 拷贝构造函数，用另一个学生对象来初始化此对象
	Student(Student* stu);

	void setstuno(string no);  //设置学号

	void setstuname(string name);  //设置姓名


	void setstumajor(string major);  //设置专业


	void setstuclass(string c); //设置班级


	void setstumobi(string mobi);  //设置手机号


	string getstuno();   //获取学号


	string getstuname();   //获取姓名


	string getstumajor();  //获取专业


	string getstuclass();   //获取班级

	string getstumobi();  //获取手机号

    // 重载等于操作符，用于比较两个学生是否相等
	bool operator == (Student s);


	Status index_stuno(string info);

	Status index_stuname(string info);

	Status index_stumajor(string info);

	Status index_stuclass(string info);

	Status index_stumobile(string info);


	Status equal_stuno(Student b);     //比较学生学号是否相同 


	Status equal_stuma_or_cl(Student b);     //比较学生的专业或班级是否相同 


	friend std::istream& operator>>(std::istream& is, Student& stu);       // 重载输入运算符，用于从输入流中读取学生信息

	friend std::ostream& operator<<(std::ostream& os, Student& stu);	    // 重载输出运算符，用于向输出流写入学生信息

    // 将学生对象的信息转换为字符串
	std::string toString();

};
