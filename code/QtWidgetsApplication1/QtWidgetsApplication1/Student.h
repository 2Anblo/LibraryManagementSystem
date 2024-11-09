# pragma once
# include "PreDefination.h"

int index(string s1, string s2, int a);

class Student
{
private:
	string studentno;      //ѧ�� 
	string studentname;    //���� 
	string studentmajor;   //רҵ 
	string studentclass;   //�༶ 
	string studentmobile;  //�ֻ� 

public:
// Ĭ�Ϲ��캯��

	Student() {};
    // �������캯��������һ��ѧ����������ʼ���˶���
	Student(Student* stu);

	void setstuno(string no);  //����ѧ��

	void setstuname(string name);  //��������


	void setstumajor(string major);  //����רҵ


	void setstuclass(string c); //���ð༶


	void setstumobi(string mobi);  //�����ֻ���


	string getstuno();   //��ȡѧ��


	string getstuname();   //��ȡ����


	string getstumajor();  //��ȡרҵ


	string getstuclass();   //��ȡ�༶

	string getstumobi();  //��ȡ�ֻ���

    // ���ص��ڲ����������ڱȽ�����ѧ���Ƿ����
	bool operator == (Student s);


	Status index_stuno(string info);

	Status index_stuname(string info);

	Status index_stumajor(string info);

	Status index_stuclass(string info);

	Status index_stumobile(string info);


	Status equal_stuno(Student b);     //�Ƚ�ѧ��ѧ���Ƿ���ͬ 


	Status equal_stuma_or_cl(Student b);     //�Ƚ�ѧ����רҵ��༶�Ƿ���ͬ 


	friend std::istream& operator>>(std::istream& is, Student& stu);       // ������������������ڴ��������ж�ȡѧ����Ϣ

	friend std::ostream& operator<<(std::ostream& os, Student& stu);	    // �������������������������д��ѧ����Ϣ

    // ��ѧ���������Ϣת��Ϊ�ַ���
	std::string toString();

};
