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
	Status ListInsert_S(Student e);   //学生表插入元素

	int ListLength_S();// 获取学生列表的长度

	Status ListDelete_S(int i, Student& e);  //删除学生表元素

	Status LocateAllElem_S(Student e, Status(Student::* compare)(Student), int* find);// 定位所有满足特定条件的学生元素

	Status GetElem_S(int i, Student& e);    //学生表La的第i个元素存于e中 

	Status SetElem_S(int i, Student e);    //学生表La的第i个元素设为e

	Status OpenStuList();                   //载入学生信息 

	Status stu_manage_output(int pos = 0);

	void Append_stu(string filename);// 将学生信息追加到指定文件

	void stu_manage_append();// 管理追加操作，可能包括将新的学生信息追加到文件或列表

	void stu_manage_delete();  //学生信息毕业处理


	void stu_manage_update();  //修改学生信息


	void stu_search_char(string info, Status(Student::* fun)(string)); //查询学生信息


	void stu_manage_search();//学生信息处理系统

	void writeToFile(const std::string& filename);    // 将学生信息写入到指定的文件

};