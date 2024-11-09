# pragma once
#include "StudentSet.h"
#pragma warning(disable:4267)

void pressanykey()              //显示"输入任意键继续"
{
	cout << "**********输入任意键继续**********\n";
	cout << "**********请勿使用方向键**********";
	char n = getchar();
	cout << endl;
	cout << "\n\n";
}

char stu_append_screen(void)    //新生入学
{
	char a;
	cout << "\n**********新生入学**********\n";
	cout << "    1、添加一个新生信息\n";
	cout << "    2、批量添加新生信息\n";
	cout << "      0、返回上一单元\n";
	cout << "请选择：";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_search_screen(void)  //学生信息查询主菜单
{
	char a;
	cout << "\n **********查询学生信息**********\n";
	cout << "          1、根据学号查询\n";
	cout << "        2、根据学生姓名查询\n";
	cout << "          3、根据专业查询\n";
	cout << "          4、根据班级查询\n";
	cout << "          5、根据手机查询\n";
	cout << "          0、返回上一单元\n";
	cout << "请选择:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_delete_screen(void)    //学生毕业菜单
{
	char a;
	cout << "**********学生毕业了**********\n";
	cout << "      1、单个学生毕业\n";
	cout << "      2、一批学生毕业\n";
	cout << "      0、返回上一单元\n";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_mana_screen(void)             //学生信息菜单 
{
	char a;
	cout << "**********学生管理主菜单**********\n";
	cout << "           1、新生入学\n";
	cout << "           2、学生毕业\n";
	cout << "         3、输出学生信息\n";
	cout << "         4、同学信息查询\n";
	cout << "         5、修改学生信息\n";
	cout << "         0、返回上一单元\n";
	cout << "请选择:\n";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

void stu_manager(StudentSet& s)
{  //学生信息印屏幕对应操作 
	char a;
	while ((a = stu_mana_screen()) != '0')
		switch (a)
		{
		case'1':system("CLS"); s.stu_manage_append();  break;   //增加学生信息 
		case'2':system("CLS"); s.stu_manage_delete();  break;   //删除学生信息 
		case'3':system("CLS"); s.stu_manage_output(); break;   //输出学生信息 
		case'4':system("CLS"); s.stu_manage_search();  break;   //查询学生信息
		case'5':system("CLS"); s.stu_manage_update();  break;   //修改学生信息 
		}
	system("CLS");
	return;
}

//StudentSet();
//virtual ~StudentSet();

Status StudentSet::ListInsert_S(Student e)   //学生表插入元素
{
	vector<Student>::iterator begin = this->begin(), end = this->end();
	if (find(begin, end, e) == this->end())
	{
		vector<Student>::push_back(e);
		return OK;
	}
	return ERROR;
}

int StudentSet::ListLength_S()
{
	return this->size();
}

Status StudentSet::ListDelete_S(int i, Student& e)  //删除学生表元素
{
	vector<Student>::iterator iter = this->begin() + i;
	e = *iter;
	this->erase(iter);
	return OK;
}

Status StudentSet::LocateAllElem_S(Student e, Status(Student::* compare)(Student), int* find)
{
	//在学生线性表中 查找所有值与e满足compare()的元素的位置地址
	//找到后将所有符合条件的元素的位置地址存放在find[]数组中，没有返回0
	int  i = 0, k = 0;
	Student* p;
	p = &this->front();                     //p初值设为第一个元素的存储位置
	while (i < this->ListLength_S())
	{
		if ((*p.*compare)(e))
		{
			find[k] = i;
			k++;
		}
		i++;
		p++;
	}
	find[k] = -1;          //以-1为满足条件的数组结束
	if (k) return OK;
	else return ERROR;
}

Status StudentSet::GetElem_S(int i, Student& e)    //学生表La的第i个元素存于e中 
{
	if (i < 0 || i >= this->ListLength_S()) return ERROR;
	vector<Student>::iterator iter = this->begin() + i;
	e = *iter;
	return OK;
}

Status StudentSet::SetElem_S(int i, Student e)    //学生表La的第i个元素设为e
{
	if (i < 0 || i >= this->ListLength_S()) return ERROR;
	vector<Student>::iterator iter = this->begin() + i;
	*iter = e;
	return OK;
}

Status StudentSet::OpenStuList()                   //载入学生信息 
{
	int  k = 0;
	Student e;
	ifstream INFILE("student1.txt");    //需事先创建存放了所有学生信息的TXT文件
	if (INFILE)
	{
		k = 0;
		while (!INFILE.eof())
		{
			INFILE >> e;
			if (e.getstuno() == "")
				break;
			this->ListInsert_S(e);//插入学生表 
		}
		INFILE.close();
		cout << "student1.txt载入已成功!\n";       //增加人机交互性
		return OK;
	}
	else { cout << "信息载入失败！请检查\n"; return ERROR; }
}

Status StudentSet::stu_manage_output(int pos)
{
	int i;
	Student e;
	if (pos > this->ListLength_S())
	{
		cout << "学生超员！\n";
		return ERROR;
	}
	//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
	vector<Student>::iterator iter = this->begin() + pos;
	for (; iter != this->end(); iter++)
	{
		e = *iter;
		cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
		i = iter - this->begin() - pos + 1;
		if (i % 20 == 0)
		{
			pressanykey();
			system("CLS");
			//if (iter < this->end())
				//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
		}
	}
	puts("\n"); return OK;
}

void StudentSet::Append_stu(string filename)
{
	int k;
	Student e;

	ifstream INFILE(filename.c_str());
	if (INFILE)
	{
		k = this->ListLength_S();
		while (!INFILE.eof())
		{
			INFILE >> e;
			if (e.getstuno() == "")
				break;
			this->ListInsert_S(e);//插入学生表
		}
		INFILE.close();

		this->stu_manage_output(k + 1);
	}

}

void StudentSet::stu_manage_append()
{
	char a;
	Student e;
	while ((a = stu_append_screen()) != '0')    //append印屏幕 
		switch (a)
		{
		case'1':     //增加单个学生信息
			cout << "输入一位新生信息:\n";
			//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
			cin >> e;
			getch();
			this->ListInsert_S(e);
			break;
		case'2':   //从文件中增加一批学生
			this->Append_stu("");   break;

		}
	system("CLS");
	return;
}

void StudentSet::stu_manage_delete()  //学生信息毕业处理
{
	char a, ch;
	string chstu;
	int find[1000];
	int position, i;
	Student e;
	while ((a = stu_delete_screen()) != '0')          //delete印屏幕 
		switch (a)
		{
		case'1':       //删除一个学生,        依据学号 
			system("CLS");
			cout << "请输入毕业生学号:" << endl;
			cin >> chstu;
			cout << endl;
			e.setstuno(chstu);
			if (this->LocateAllElem_S(e, &Student::equal_stuno, find))
			{
				//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
				position = find[0];
				this->GetElem_S(position, e);
				cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
				cout << "确定是这个同学毕业么？ (y/n)";
				ch = getche();
				cout << endl;
				if (ch == 'Y' || ch == 'y')
				{
					this->ListDelete_S(position, e);
					cout << "删除成功" << endl;
				}
			}
			else
				cout << "未找到该同学!\n";
			break;
		case'2':            //根据班级或专业删除一批学生
			cout << "请输入毕业同学班级或专业:";
			cout << endl;
			cin >> chstu;
			cout << endl;
			e.setstumajor(chstu);
			e.setstuclass(chstu);
			if (this->LocateAllElem_S(e, &Student::equal_stuma_or_cl, find))
			{
				//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
				i = 0;
				while ((position = find[i]) != -1)
				{
					this->GetElem_S(position, e);
					cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
					i++;
				}
				cout << "是否确定这些同学都已毕业？(y/n)";
				ch = getche();
				cout << endl;
				if (ch == 'Y' || ch == 'y') i--;          //倒着删除
				while (i >= 0 && find[i] != -1)
				{
					position = find[i];
					this->ListDelete_S(position, e);        //一个一个从后往前删除学生信息 
					i--;
				}
			}
			else
				cout << "未找到该同学!\n";
			break;
		}
	return;
}

void StudentSet::stu_manage_update()  //修改学生信息
{
	string chstu, ch, judge;
	Student e;
	int position, find[1000];
	cout << "修改学生数据,学号不可修改且每次只能改一项!";
	cout << "输入需要修改数据的学生学号,输入0表示放弃!\n";
	getline(cin, chstu);
	if (chstu == "0") return;
	e.setstuno(chstu);
	if (this->LocateAllElem_S(e, &Student::equal_stuno, find))
	{
		//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
		position = find[0];
		this->GetElem_S(position, e);
		cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
		cout << "是否确定修改此学生?(y/n)";
		getline(cin, ch);
		if (ch == "Y" || ch == "y")
		{
			cout << "\n 姓名修改为: (默认不修改为回车)";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstuname(chstu);
			cout << "专业修改为:(默认不修改为回车):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstumajor(chstu);
			cout << "班级修改为:(默认不修改为回车):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstuclass(chstu);
			cout << "手机修改为:(默认不修改为回车):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstumobi(chstu);
			cout << "完成修改!\n";
			cout << "此同学信息已更新!\n";
			cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
			cout << "数据是否正确? Y/N";           //加强人机交互性,给予修改与否的反馈
			getline(cin, judge);
			if (judge == "Y" || judge == "y")
				this->SetElem_S(position, e);
			else
				cout << "修改失败!" << endl;
		}
	}
	else
		cout << "未找到该同学!!\n";
}

void StudentSet::stu_search_char(string info, Status(Student::* fun)(string)) //查询学生信息
{
	int j, count = 0;
	int first = 0, find = 0;
	Student e;
	for (j = 0; j < this->ListLength_S(); j++)
	{
		this->GetElem_S(j, e);      //提出每个学生信息
		if ((e.*fun)(info))         //查询含info的学生
		{
			find = 1;        //找到设find为1
			count++;       //计数器加1
			if (!first)     //输出学生信息
			{
				//cout << setw(10) << "学号" << setw(9) << "姓名" << setw(18) << "专业" << setw(10) << "班级" << setw(12) << "手机号码" << endl;
				first = 1;
			}
			cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
			if (count % 20 == 0)           //20一断 20一断 
			{
				pressanykey(); first = 0;
			}
		}
	}
	if (count)
		//cout << "\n共找到" << count << "个!\n";
	//else
	//	cout << "\n没有找到符合条件的学生!\n";
	return;
}

void StudentSet::stu_manage_search()
{  //学生信息处理系统
	char a;
	string information_char;
	int(Student:: * func_char)(string);
	Student e;
	while ((a = stu_search_screen()) != '0')
		switch (a)
		{
		case'1': //根据学号查询
			cout << "***学号查询***   请输入学号:";
			cin >> information_char;   //输入全部或部分特定学号
			func_char = &Student::index_stuno;    //调用学号查找函数
			this->stu_search_char(information_char, func_char); break;
		case'2': //根据姓名查询
			cout << "***姓名查询***   请输入姓名:";
			cin >> information_char;  //输入全名或部分特定字
			func_char = &Student::index_stuname;
			this->stu_search_char(information_char, func_char); break;
		case'3': //根据专业查询
			cout << "***专业查询***   请输入专业:";
			cin >> information_char;  //输入专业名或特定字符
			func_char = &Student::index_stumajor;
			this->stu_search_char(information_char, func_char); break;
		case'4': //根据班级查询
			cout << "***班级查询***   请输入班级:";
			cin >> information_char;   //输入班级名或特定字符
			func_char = &Student::index_stuclass;
			this->stu_search_char(information_char, func_char); break;
		case'5': //根据手机号查询
			cout << "***手机号查询***   请输入手机号:";
			cin >> information_char;  //输入手机号或特定数字
			func_char = &Student::index_stumobile;
			this->stu_search_char(information_char, func_char); break;
		}
	return;
}

void StudentSet::writeToFile(const std::string& filename) {
	std::ofstream outfile(filename);
	int flag = 0;
	if (outfile.is_open()) {
		for (auto& student : *this) {
			if(flag)
			outfile << std::endl << student.toString() ;
			else
			{
				outfile << student.toString();
				flag = 1;
			}
		}
		outfile.close();
	}
	return;
}