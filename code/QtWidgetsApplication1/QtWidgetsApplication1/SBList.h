#pragma once
# include "StudentNodeSet.h"
#include "PreDefination.h"


class SBList
{
private:
	int studentnum;             //�����鼮������ 
	int borrownum;              //���ȥ�������� 
	StudentNodeSet sblist;    //ѧ�����ı� 
public:
    // ��ʼһ���µĽ�������

	Status begin_borrow();
    // �򿪲����ؽ����б�ͨ�����ļ��ж�ȡ

	Status OpenBorrowList();
    // ����ǰ�Ľ�����Ϣд�뵽�ļ���

	Status WriteToFile();
    // ���ָ��ѧ���Ƿ����ڽ����б���

	int StuWhetherIn(string no);

    // ������б������һ���µ�ѧ���ڵ�
	void pushelem(StudentNode sn);

    // ���õ�ǰ�����鼮������
	void setstudentnum(int s);

    // ���ý��ȥ���鼮����
	void setborrownum(int b);

    // ��ȡ��ǰ�����鼮������
	int getstudentnum();

    // ��ȡ���ȥ���鼮����
	int getborrownum();

    // ��ȡָ��ѧ���ĸ��˽����鼮����
	int getpersonalnum(string no);

    // ���ָ���鼮�Ƿ��ѱ�ָ��ѧ������
	int BookWhetherIn(string sn, string bn);

    // Ϊָ��ѧ�����һ���µĽ��Ĺ�ϵ
	void addanewrelation(string sn, BorrowInfo bi);

    // ѧ���黹һ����
	void returnbook(string sn, string bn);

    // ��ӡָ��ѧ�������н�����Ϣ
	void printbookinfo(string sn);

    // ��ӡ��һ�鼮�Ľ�����Ϣ
	void printsinglebookinfo(string bn);

    // ���½����б��е������鼮��Ϣ
	void outdate(Date now, StudentSet stu);

    // ��ȡѧ�����Ľڵ㼯
	StudentNodeSet getSBList();

    // ���ָ��ѧ���Ľ��������Ƿ�ﵽ����
	bool bookLimit(string sn);

};