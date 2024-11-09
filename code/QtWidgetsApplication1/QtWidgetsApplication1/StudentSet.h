# pragma once
# include "Student.h"
#include "PreDefination.h"


class StudentSet;

void pressanykey();
char stu_append_screen();
char stu_search_screen(void);
char stu_delete_screen(void);
char stu_mana_screen(void);
void stu_manager(StudentSet& s);


class StudentSet :public vector < Student >
{
public:
	//StudentSet();
	//virtual ~StudentSet();
	Status ListInsert_S(Student e);   //ѧ�������Ԫ��

	int ListLength_S();// ��ȡѧ���б�ĳ���

	Status ListDelete_S(int i, Student& e);  //ɾ��ѧ����Ԫ��

	Status LocateAllElem_S(Student e, Status(Student::* compare)(Student), int* find);// ��λ���������ض�������ѧ��Ԫ��

	Status GetElem_S(int i, Student& e);    //ѧ����La�ĵ�i��Ԫ�ش���e�� 

	Status SetElem_S(int i, Student e);    //ѧ����La�ĵ�i��Ԫ����Ϊe

	Status OpenStuList();                   //����ѧ����Ϣ 

	Status stu_manage_output(int pos = 0);

	void Append_stu(string filename);// ��ѧ����Ϣ׷�ӵ�ָ���ļ�

	void stu_manage_append();// ����׷�Ӳ��������ܰ������µ�ѧ����Ϣ׷�ӵ��ļ����б�

	void stu_manage_delete();  //ѧ����Ϣ��ҵ����


	void stu_manage_update();  //�޸�ѧ����Ϣ


	void stu_search_char(string info, Status(Student::* fun)(string)); //��ѯѧ����Ϣ


	void stu_manage_search();//ѧ����Ϣ����ϵͳ

	void writeToFile(const std::string& filename);    // ��ѧ����Ϣд�뵽ָ�����ļ�

};