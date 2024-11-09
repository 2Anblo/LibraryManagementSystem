# include "BookSet.h"

void pressanykey(int a)              //��ʾ"�������������"
{
	cout << "**********�������������**********\n";
	cout << "**********����ʹ�÷����**********";
	char n = getchar();
	cout << endl;
	cout << "\n\n";
}

char book_search_screen(void)  //ͼ���ѯ���˵�
{
	char a;
	cout << "\n**********��ѯͼ����Ϣ**********\n";
	cout << "      1�����ݳ�������Ϣ��ѯ\n";
	cout << "      2������ͼ�����Ʋ�ѯ\n";
	cout << "         3���������߲�ѯ\n";
	cout << "       4�����ݳ������ڲ�ѯ\n";
	cout << "         5��������Ų�ѯ\n";
	cout << "        6���ɽ���ͼ���ѯ\n";
	cout << "         0��������һ��Ԫ\n";
	//cout << "�����:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char book_append_screen(void)   //���ͼ�����˵�
{
	char a;
	cout << "\n**********���ͼ����Ϣ**********\n";
	cout << "       1������ͼ����Ϣ���\n";
	cout << "       2������ͼ����Ϣ���\n";
	cout << "        0��������һ��Ԫ\n";
	cout << "��ѡ��:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char book_manager_screen(void)     //ͼ�����˵�
{
	char a;
	cout << "\n**********ͼ����Ϣ����**********\n";
	cout << "           1����������\n";
	cout << "         2��ͼ����Ϣ��ѯ\n";
	cout << "        3����ʾ����ͼ����Ϣ\n";
	cout << "         0��������һ��Ԫ\n";
	cout << "��ѡ��:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

void book_manager(BookSet& b)    //ͼ�����˵��������
{
	char a;
	while ((a = book_manager_screen()) != '0')
		switch (a)
		{
		case'1': system("CLS"); b.book_manage_append();
			break;
		case'2': system("CLS"); b.book_manage_search();
			break;
		case'3': system("CLS"); b.Output_Book(1);
			break;
		}
	system("CLS");
	return;
}

//BookSet();
//virtual ~BookSet();

int BookSet::ListLength_B()
{
	return this->size();
}

Status BookSet::ListInsert_B(Book e)
{
	vector<Book>::iterator begin = this->begin(), end = this->end();
	if (find(begin, end, e) == this->end())
	{
		vector<Book>::push_back(e);
		return OK;
	}
	return ERROR;
}

Status BookSet::LocateAllElem_B(Book e, Status(*compare)(Book, Book), int* find)
{
	//��ͼ�����Ա��� ��������ֵ��e����compare()��Ԫ�ص�λ�õ�ַ
	//�ҵ������з���������Ԫ�ص�λ�õ�ַ�����find[]�����У�û���򷵻�0
	int i, k;
	Book* p;
	i = 0; k = 0;
	p = &this->front();       //��һԪ�ش洢λ��
	while (i < this->ListLength_B())
	{
		if ((*compare)(*p, e))
		{
			find[k] = i; k++;
		}
		i++; p++;
	}
	find[k] = -1;              //��-1Ϊfind���� 
	if (k) return OK;
	else return ERROR;
}

Status BookSet::GetElem_B(int i, Book& e)
{   //��ȡͼ���L�ĵ�i��Ԫ�� ������e�� 
	if (i < 0 || i >= this->ListLength_B()) return ERROR;
	vector<Book>::iterator iter = this->begin() + i;
	e = *iter;
	return OK;
}

Status BookSet::SetElem_B(int i, Book e)
{   //��ͼ���L�ĵ�i��Ԫ�ظ�ֵΪe
	if (i < 0 || i >= this->ListLength_B()) return ERROR;
	vector<Book>::iterator iter = this->begin() + i;
	*iter = e;
	return OK;
}

void BookSet::OpenBookList()  //����TXT��ͼ����Ϣ
{
	int i = 0, j = 0, k = 0;
	Book e;
	ifstream INFILE("book.txt");   //�����ͼ����Ϣ�� ���ݴ��ڴ��ļ���		
	if (INFILE)
	{
		k = 0;
		while (!INFILE.eof())
		{
			INFILE >> e;
			if (e.getbookno() == "")
				break;
			this->ListInsert_B(e);   //������ 
		}
		INFILE.close();
		cout << "ͼ����Ϣ����ɹ�\n";
	}
	return;
}

void BookSet::Output_Book(int pos)    //�ӵ�pos����ʼ����Ժ������ͼ����Ϣ
{
	int i;
	Book e;
	if (pos > this->ListLength_B())
	{
		cout << "ͼ�鳬��!\n";
		return;
	}
	vector<Book>::iterator iter = this->begin() + pos;
	for (; iter != this->end(); iter++)
	{
		e = *iter;
		cout << setw(6) << e.getbookno() << setw(20) << e.getbookname() << setw(8) << e.getauthor() << setw(16) << e.getpublisher() << setw(2) << e.gettotalnum() << setw(2) << e.gettotalnum() - e.getborrownum() << setw(10) << e.getpubday() << endl;
		i = iter - this->begin() - pos + 1;
		if (i % 20 == 0)
		{
			pressanykey(1);    //20��һ��
			system("CLS");
			//if (iter < this->end())
				//cout << setw(6) << "���" << setw(20) << "����" << setw(8) << "����" << setw(16) << "������" << setw(9) << "�ܴ����" << setw(9) << "�ܽ���" << setw(10) << "��������" << endl;
		}
	}
	cout << endl;
}

void BookSet::Append_book(string filename)   //��������ͼ��
{
	int k;
	//string filename;
	//cout << "**********�¼���һ������**********\n";
	//cout << "���뵼�������ļ���:";
	//cin >> filename;
	ifstream INFILE(filename.c_str());
	if (INFILE)
	{
		k = this->ListLength_B();
		while (!INFILE.eof())
		{
			Book e;
			string notemp, nametemp, authortemp, pubtemp;
			int totaltemp;
			Date temp;
			INFILE >> notemp;
			e.setbookno(notemp);
			INFILE >> nametemp;
			e.setbookname(nametemp);
			INFILE >> authortemp;
			e.setauthor(authortemp);
			INFILE >> pubtemp;
			e.setpublisher(pubtemp);
			INFILE >> totaltemp;
			e.settotal(totaltemp);
			e.setborrow(0);   //��ʼ�����������
			INFILE >> temp;
			e.setday(temp);
			if (e.getbookno() == "")
				break;
			this->ListInsert_B(e);
		}
		INFILE.close();
		//cout << "**********�¼�������һ������ ��˶�**********\n";
		this->Output_Book(k + 1);
	}
	//else
		//cout << "û���ҵ����ļ�!\n";
}

void BookSet::book_manage_append()   //ͼ�����Ӵ���
{
	char a;
	Book e;
	while ((a = book_append_screen()) != '0')
		switch (a)
		{
		case'1':                   //ֻ��һ����
			cout << "�����뵥���������Ϣ:\n";
			cin >> e;
			e.setborrow(0);   //��ʼ��������
			this->ListInsert_B(e);   //����ĩβ
			break;
		case'2':                  //���ļ�������һ����
			this->Append_book("");
			break;
		}
	return;
}

void BookSet::book_search_char(string info, int(Book::* f)(string))    //��ѯͼ����Ϣ
{     //���������򲿷�,������а���info���鼮
	int i, count = 0;
	int flag = 0;
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);           //���ÿһ���鼮����
		if ((e.*f)(info))            //���Һ�info���鼮
		{
			count++;       //�ҵ���������1
			if (!flag)         //flag��־ ÿһ�ϵĵ�һ���������ͷ 
			{
				//cout << setw(6) << "���" << setw(10) << "����" << setw(8) << "����" << setw(10) << "������" << setw(9) << "�ܴ����" << setw(9) << "�ܽ���" << setw(10) << "��������" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10) << e.getpubday() << endl;
			if (count % 20 == 0)       //ÿ20��  �Ͽ�һ��
			{
				pressanykey(1); flag = 0;
			}
		}
	}
	if (count)
		cout << "\n���ҵ�" << count << "����\n";
	else
		cout << "\nû���ҵ������������鼮!\n";
	return;
}

void BookSet::book_search_have()         //��ѯ���ж�����ɽ� 
{
	int i, count = 0;
	int flag = 0;    //��ͷ��־
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);        //��������鼮
		if (e.gettotalnum() - e.getborrownum() > 0)      //ʣ���鼮һ������
		{
			count++;            //ʣ��������1 
			if (!flag)
			{
				//cout << setw(6) << "���" << setw(30) << "����" << setw(8) << "����" << setw(20) << "������" << setw(4) << "�ܴ����" << setw(4) << "�ܽ���" << setw(10) << "��������" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10) << e.getpubday() << endl;
			if (count % 20 == 0)       //ÿ20��  �Ͽ�һ��
			{
				pressanykey(1); flag = 0;
			}
		}

	}
	if (count)
		cout << "\n���ҵ�" << count << "����\n";
	else
		cout << "\nû���ҵ������������鼮!\n";
	return;
}

void BookSet::book_search_date(int year, int month)
{  //���ݳ������²�ѯ�鼮 
	int i, count = 0;
	int flag = 0;
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);          //���ÿһ���鼮��Ϣ
		if (e.getpubday().getyear() == year && e.getpubday().getmonth() == month)    //������������ȫһ��
		{
			count++;
			if (!flag)
			{
				//cout << setw(6) << "���" << setw(30) << "����" << setw(8) << "����" << setw(20) << "������" << setw(4) << "�ܴ����" << setw(4) << "�ܽ���" << setw(10) << "��������" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10);
			cout << e.getpubday() << endl;
			if (count % 20 == 0)       //ÿ20��  �Ͽ�һ��
			{
				pressanykey(1); flag = 0;
			}
		}
	}
	if (count)
		cout << "\n���ҵ�" << count << "����\n";
	else
		cout << "\nû���ҵ������������鼮!\n";
	return;
}

void BookSet::book_manage_search()
{
	char a;
	string infor;
	int year, month;
	int (Book:: * f)(string);
	Book e;
	while ((a = book_search_screen()) != '0')
		switch (a) {
		case'1':cout << "���������ѯ�鼮����������س���������:";
			cin >> infor;
			cout << endl;
			f = &Book::index_publisher;                 //index_publisher(e,infor)
			this->book_search_char(infor, f);
			break;
		case'2':cout << "��������ѯ�鼮,����������:";
			cin >> infor;
			cout << endl;
			f = &Book::index_bookname;
			this->book_search_char(infor, f); break;
		case'3':cout << "������������ѯ�鼮,��������������:";
			cin >> infor;
			cout << endl;
			f = &Book::index_author;
			this->book_search_char(infor, f); break;
		case'4':cout << "������ʱ���ѯ�鼮,�������������:";
			cin >> year >> month;
			cout << endl;
			this->book_search_date(year, month);	break;
		case'5':cout << "����Ų�ѯ�鼮,���������:";
			cin >> infor;
			cout << endl;
			f = &Book::index_bookno;
			this->book_search_char(infor, f); break;
		case'6':  //ʣ��ɽ���ͼ������
			this->book_search_have();
			break;
		}
	return;
}


void BookSet::writeToFile(const std::string& filename) {
	std::ofstream outfile(filename);
	if (outfile.is_open()) {
		int flag = 0;
		for (auto& book : *this) {
			if(flag)
			outfile << std::endl << book.toString() ;
			else
			{
				outfile << book.toString();
				flag = 1;
			}
		}
		outfile.close();
	}
}


void BookSet::borrowBook(string bookNo) {

	for (auto it = this->begin(); it != this->end(); it++)
	{
		if (it->getbookno() == bookNo) {
			it->setborrow(it->getborrownum() + 1);
			return;
		}
	}
}

void BookSet::returnBook(string bookNo) {
	for (auto it = this->begin(); it != this->end(); it++)
	{
		if (it->getbookno() == bookNo) {
			it->setborrow(it->getborrownum() - 1);
			return;
		}
	}
}
