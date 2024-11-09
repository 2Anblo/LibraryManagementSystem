# pragma once
# include "Date.h"
#include "PreDefination.h"


int index(string s1, string s2);

class Book
{
private:
	string bookno;    	 //��� 
	string bookname;      //���� 
	string author;    	 //���� 
	string publisher;      //������ 
	int totalnum;			 //�ݲ�ͼ���� 
	int borrownum;           //������� 
	Date pubday;             //�������� 

public:
// �������
	void setbookno(string no);
 // ��������
	void setbookname(string name);
 // ����������
	void setauthor(string au);
// ���ó�����
	void setpublisher(string pub);
 // ���ùݲ�����
	void settotal(int i);
// ���ý������
	void setborrow(int i);
 // ���ó�������
	void setday(Date t);
 // ��ȡ���
	string getbookno();
 // ��ȡ����
	string getbookname();
// ��ȡ������
	string getauthor();
// ��ȡ����������
	string getpublisher();
// ��ȡ�ݲ�����
	int gettotalnum();
// ��ȡ�������
	int getborrownum();
// ��ȡ��������
	Date& getpubday();
 // ���������������Ƚ��������Ƿ����
	bool operator == (Book b);
 // ������ָ�����ƥ����鼮
	Status index_bookno(string info);
	 // ������ָ������ƥ����鼮
	Status index_author(string info)
		;
		 // ������ָ������ƥ����鼮
	Status index_bookname(string info);
	 // ������ָ��������ƥ����鼮
	Status index_publisher(string info);

	friend std::istream& operator>>(std::istream& is, Book& boo);   //����������������
	friend std::ostream& operator<<(std::ostream& os, Book& boo);	 // �������������������������д���鼮��Ϣ
	friend bool operator ==(Book& book1, Book& book2);	// ����ȫ���������������ڱȽ��������Ƿ���ȫ��ͬ
 // ���鼮��Ϣת��Ϊ�ַ�����ʽ
	std::string toString();

};
