# pragma once
#include "StudentSet.h"
#pragma warning(disable:4267)

void pressanykey()              //��ʾ"�������������"
{
	cout << "**********�������������**********\n";
	cout << "**********����ʹ�÷����**********";
	char n = getchar();
	cout << endl;
	cout << "\n\n";
}

char stu_append_screen(void)    //������ѧ
{
	char a;
	cout << "\n**********������ѧ**********\n";
	cout << "    1�����һ��������Ϣ\n";
	cout << "    2���������������Ϣ\n";
	cout << "      0��������һ��Ԫ\n";
	cout << "��ѡ��";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_search_screen(void)  //ѧ����Ϣ��ѯ���˵�
{
	char a;
	cout << "\n **********��ѯѧ����Ϣ**********\n";
	cout << "          1������ѧ�Ų�ѯ\n";
	cout << "        2������ѧ��������ѯ\n";
	cout << "          3������רҵ��ѯ\n";
	cout << "          4�����ݰ༶��ѯ\n";
	cout << "          5�������ֻ���ѯ\n";
	cout << "          0��������һ��Ԫ\n";
	cout << "��ѡ��:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_delete_screen(void)    //ѧ����ҵ�˵�
{
	char a;
	cout << "**********ѧ����ҵ��**********\n";
	cout << "      1������ѧ����ҵ\n";
	cout << "      2��һ��ѧ����ҵ\n";
	cout << "      0��������һ��Ԫ\n";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char stu_mana_screen(void)             //ѧ����Ϣ�˵� 
{
	char a;
	cout << "**********ѧ���������˵�**********\n";
	cout << "           1��������ѧ\n";
	cout << "           2��ѧ����ҵ\n";
	cout << "         3�����ѧ����Ϣ\n";
	cout << "         4��ͬѧ��Ϣ��ѯ\n";
	cout << "         5���޸�ѧ����Ϣ\n";
	cout << "         0��������һ��Ԫ\n";
	cout << "��ѡ��:\n";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

void stu_manager(StudentSet& s)
{  //ѧ����Ϣӡ��Ļ��Ӧ���� 
	char a;
	while ((a = stu_mana_screen()) != '0')
		switch (a)
		{
		case'1':system("CLS"); s.stu_manage_append();  break;   //����ѧ����Ϣ 
		case'2':system("CLS"); s.stu_manage_delete();  break;   //ɾ��ѧ����Ϣ 
		case'3':system("CLS"); s.stu_manage_output(); break;   //���ѧ����Ϣ 
		case'4':system("CLS"); s.stu_manage_search();  break;   //��ѯѧ����Ϣ
		case'5':system("CLS"); s.stu_manage_update();  break;   //�޸�ѧ����Ϣ 
		}
	system("CLS");
	return;
}

//StudentSet();
//virtual ~StudentSet();

Status StudentSet::ListInsert_S(Student e)   //ѧ�������Ԫ��
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

Status StudentSet::ListDelete_S(int i, Student& e)  //ɾ��ѧ����Ԫ��
{
	vector<Student>::iterator iter = this->begin() + i;
	e = *iter;
	this->erase(iter);
	return OK;
}

Status StudentSet::LocateAllElem_S(Student e, Status(Student::* compare)(Student), int* find)
{
	//��ѧ�����Ա��� ��������ֵ��e����compare()��Ԫ�ص�λ�õ�ַ
	//�ҵ������з���������Ԫ�ص�λ�õ�ַ�����find[]�����У�û�з���0
	int  i = 0, k = 0;
	Student* p;
	p = &this->front();                     //p��ֵ��Ϊ��һ��Ԫ�صĴ洢λ��
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
	find[k] = -1;          //��-1Ϊ�����������������
	if (k) return OK;
	else return ERROR;
}

Status StudentSet::GetElem_S(int i, Student& e)    //ѧ����La�ĵ�i��Ԫ�ش���e�� 
{
	if (i < 0 || i >= this->ListLength_S()) return ERROR;
	vector<Student>::iterator iter = this->begin() + i;
	e = *iter;
	return OK;
}

Status StudentSet::SetElem_S(int i, Student e)    //ѧ����La�ĵ�i��Ԫ����Ϊe
{
	if (i < 0 || i >= this->ListLength_S()) return ERROR;
	vector<Student>::iterator iter = this->begin() + i;
	*iter = e;
	return OK;
}

Status StudentSet::OpenStuList()                   //����ѧ����Ϣ 
{
	int  k = 0;
	Student e;
	ifstream INFILE("student1.txt");    //�����ȴ������������ѧ����Ϣ��TXT�ļ�
	if (INFILE)
	{
		k = 0;
		while (!INFILE.eof())
		{
			INFILE >> e;
			if (e.getstuno() == "")
				break;
			this->ListInsert_S(e);//����ѧ���� 
		}
		INFILE.close();
		cout << "student1.txt�����ѳɹ�!\n";       //�����˻�������
		return OK;
	}
	else { cout << "��Ϣ����ʧ�ܣ�����\n"; return ERROR; }
}

Status StudentSet::stu_manage_output(int pos)
{
	int i;
	Student e;
	if (pos > this->ListLength_S())
	{
		cout << "ѧ����Ա��\n";
		return ERROR;
	}
	//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
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
				//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
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
			this->ListInsert_S(e);//����ѧ����
		}
		INFILE.close();

		this->stu_manage_output(k + 1);
	}

}

void StudentSet::stu_manage_append()
{
	char a;
	Student e;
	while ((a = stu_append_screen()) != '0')    //appendӡ��Ļ 
		switch (a)
		{
		case'1':     //���ӵ���ѧ����Ϣ
			cout << "����һλ������Ϣ:\n";
			//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
			cin >> e;
			getch();
			this->ListInsert_S(e);
			break;
		case'2':   //���ļ�������һ��ѧ��
			this->Append_stu("");   break;

		}
	system("CLS");
	return;
}

void StudentSet::stu_manage_delete()  //ѧ����Ϣ��ҵ����
{
	char a, ch;
	string chstu;
	int find[1000];
	int position, i;
	Student e;
	while ((a = stu_delete_screen()) != '0')          //deleteӡ��Ļ 
		switch (a)
		{
		case'1':       //ɾ��һ��ѧ��,        ����ѧ�� 
			system("CLS");
			cout << "�������ҵ��ѧ��:" << endl;
			cin >> chstu;
			cout << endl;
			e.setstuno(chstu);
			if (this->LocateAllElem_S(e, &Student::equal_stuno, find))
			{
				//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
				position = find[0];
				this->GetElem_S(position, e);
				cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
				cout << "ȷ�������ͬѧ��ҵô�� (y/n)";
				ch = getche();
				cout << endl;
				if (ch == 'Y' || ch == 'y')
				{
					this->ListDelete_S(position, e);
					cout << "ɾ���ɹ�" << endl;
				}
			}
			else
				cout << "δ�ҵ���ͬѧ!\n";
			break;
		case'2':            //���ݰ༶��רҵɾ��һ��ѧ��
			cout << "�������ҵͬѧ�༶��רҵ:";
			cout << endl;
			cin >> chstu;
			cout << endl;
			e.setstumajor(chstu);
			e.setstuclass(chstu);
			if (this->LocateAllElem_S(e, &Student::equal_stuma_or_cl, find))
			{
				//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
				i = 0;
				while ((position = find[i]) != -1)
				{
					this->GetElem_S(position, e);
					cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
					i++;
				}
				cout << "�Ƿ�ȷ����Щͬѧ���ѱ�ҵ��(y/n)";
				ch = getche();
				cout << endl;
				if (ch == 'Y' || ch == 'y') i--;          //����ɾ��
				while (i >= 0 && find[i] != -1)
				{
					position = find[i];
					this->ListDelete_S(position, e);        //һ��һ���Ӻ���ǰɾ��ѧ����Ϣ 
					i--;
				}
			}
			else
				cout << "δ�ҵ���ͬѧ!\n";
			break;
		}
	return;
}

void StudentSet::stu_manage_update()  //�޸�ѧ����Ϣ
{
	string chstu, ch, judge;
	Student e;
	int position, find[1000];
	cout << "�޸�ѧ������,ѧ�Ų����޸���ÿ��ֻ�ܸ�һ��!";
	cout << "������Ҫ�޸����ݵ�ѧ��ѧ��,����0��ʾ����!\n";
	getline(cin, chstu);
	if (chstu == "0") return;
	e.setstuno(chstu);
	if (this->LocateAllElem_S(e, &Student::equal_stuno, find))
	{
		//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
		position = find[0];
		this->GetElem_S(position, e);
		cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
		cout << "�Ƿ�ȷ���޸Ĵ�ѧ��?(y/n)";
		getline(cin, ch);
		if (ch == "Y" || ch == "y")
		{
			cout << "\n �����޸�Ϊ: (Ĭ�ϲ��޸�Ϊ�س�)";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstuname(chstu);
			cout << "רҵ�޸�Ϊ:(Ĭ�ϲ��޸�Ϊ�س�):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstumajor(chstu);
			cout << "�༶�޸�Ϊ:(Ĭ�ϲ��޸�Ϊ�س�):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstuclass(chstu);
			cout << "�ֻ��޸�Ϊ:(Ĭ�ϲ��޸�Ϊ�س�):";
			getline(cin, chstu);
			cout << endl;
			if (chstu != "")
				e.setstumobi(chstu);
			cout << "����޸�!\n";
			cout << "��ͬѧ��Ϣ�Ѹ���!\n";
			cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
			cout << "�����Ƿ���ȷ? Y/N";           //��ǿ�˻�������,�����޸����ķ���
			getline(cin, judge);
			if (judge == "Y" || judge == "y")
				this->SetElem_S(position, e);
			else
				cout << "�޸�ʧ��!" << endl;
		}
	}
	else
		cout << "δ�ҵ���ͬѧ!!\n";
}

void StudentSet::stu_search_char(string info, Status(Student::* fun)(string)) //��ѯѧ����Ϣ
{
	int j, count = 0;
	int first = 0, find = 0;
	Student e;
	for (j = 0; j < this->ListLength_S(); j++)
	{
		this->GetElem_S(j, e);      //���ÿ��ѧ����Ϣ
		if ((e.*fun)(info))         //��ѯ��info��ѧ��
		{
			find = 1;        //�ҵ���findΪ1
			count++;       //��������1
			if (!first)     //���ѧ����Ϣ
			{
				//cout << setw(10) << "ѧ��" << setw(9) << "����" << setw(18) << "רҵ" << setw(10) << "�༶" << setw(12) << "�ֻ�����" << endl;
				first = 1;
			}
			cout << setw(10) << e.getstuno() << setw(9) << e.getstuname() << setw(18) << e.getstumajor() << setw(10) << e.getstuclass() << setw(12) << e.getstumobi() << endl;
			if (count % 20 == 0)           //20һ�� 20һ�� 
			{
				pressanykey(); first = 0;
			}
		}
	}
	if (count)
		//cout << "\n���ҵ�" << count << "��!\n";
	//else
	//	cout << "\nû���ҵ�����������ѧ��!\n";
	return;
}

void StudentSet::stu_manage_search()
{  //ѧ����Ϣ����ϵͳ
	char a;
	string information_char;
	int(Student:: * func_char)(string);
	Student e;
	while ((a = stu_search_screen()) != '0')
		switch (a)
		{
		case'1': //����ѧ�Ų�ѯ
			cout << "***ѧ�Ų�ѯ***   ������ѧ��:";
			cin >> information_char;   //����ȫ���򲿷��ض�ѧ��
			func_char = &Student::index_stuno;    //����ѧ�Ų��Һ���
			this->stu_search_char(information_char, func_char); break;
		case'2': //����������ѯ
			cout << "***������ѯ***   ����������:";
			cin >> information_char;  //����ȫ���򲿷��ض���
			func_char = &Student::index_stuname;
			this->stu_search_char(information_char, func_char); break;
		case'3': //����רҵ��ѯ
			cout << "***רҵ��ѯ***   ������רҵ:";
			cin >> information_char;  //����רҵ�����ض��ַ�
			func_char = &Student::index_stumajor;
			this->stu_search_char(information_char, func_char); break;
		case'4': //���ݰ༶��ѯ
			cout << "***�༶��ѯ***   ������༶:";
			cin >> information_char;   //����༶�����ض��ַ�
			func_char = &Student::index_stuclass;
			this->stu_search_char(information_char, func_char); break;
		case'5': //�����ֻ��Ų�ѯ
			cout << "***�ֻ��Ų�ѯ***   �������ֻ���:";
			cin >> information_char;  //�����ֻ��Ż��ض�����
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