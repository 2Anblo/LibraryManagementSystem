# include "BookSet.h"

void pressanykey(int a)              //显示"输入任意键继续"
{
	cout << "**********输入任意键继续**********\n";
	cout << "**********请勿使用方向键**********";
	char n = getchar();
	cout << endl;
	cout << "\n\n";
}

char book_search_screen(void)  //图书查询主菜单
{
	char a;
	cout << "\n**********查询图书信息**********\n";
	cout << "      1、根据出版社信息查询\n";
	cout << "      2、根据图书名称查询\n";
	cout << "         3、根据作者查询\n";
	cout << "       4、根据出版日期查询\n";
	cout << "         5、根据书号查询\n";
	cout << "        6、可借阅图书查询\n";
	cout << "         0、返回上一单元\n";
	//cout << "请输出:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char book_append_screen(void)   //添加图书主菜单
{
	char a;
	cout << "\n**********添加图书信息**********\n";
	cout << "       1、单本图书信息添加\n";
	cout << "       2、批量图书信息添加\n";
	cout << "        0、返回上一单元\n";
	cout << "请选择:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

char book_manager_screen(void)     //图书管理菜单
{
	char a;
	cout << "\n**********图书信息管理**********\n";
	cout << "           1、来新书了\n";
	cout << "         2、图书信息查询\n";
	cout << "        3、显示所有图书信息\n";
	cout << "         0、返回上一单元\n";
	cout << "请选择:";
	a = getche();
	cout << "\n";
	system("CLS");
	return a;
}

void book_manager(BookSet& b)    //图书管理菜单处理程序
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
	//在图书线性表中 查找所有值与e满足compare()的元素的位置地址
	//找到后将所有符合条件的元素的位置地址存放在find[]数组中，没有则返回0
	int i, k;
	Book* p;
	i = 0; k = 0;
	p = &this->front();       //第一元素存储位置
	while (i < this->ListLength_B())
	{
		if ((*compare)(*p, e))
		{
			find[k] = i; k++;
		}
		i++; p++;
	}
	find[k] = -1;              //以-1为find结束 
	if (k) return OK;
	else return ERROR;
}

Status BookSet::GetElem_B(int i, Book& e)
{   //获取图书表L的第i个元素 并存于e中 
	if (i < 0 || i >= this->ListLength_B()) return ERROR;
	vector<Book>::iterator iter = this->begin() + i;
	e = *iter;
	return OK;
}

Status BookSet::SetElem_B(int i, Book e)
{   //将图书表L的第i个元素赋值为e
	if (i < 0 || i >= this->ListLength_B()) return ERROR;
	vector<Book>::iterator iter = this->begin() + i;
	*iter = e;
	return OK;
}

void BookSet::OpenBookList()  //载入TXT的图书信息
{
	int i = 0, j = 0, k = 0;
	Book e;
	ifstream INFILE("book.txt");   //将存放图书信息的 数据存于此文件中		
	if (INFILE)
	{
		k = 0;
		while (!INFILE.eof())
		{
			INFILE >> e;
			if (e.getbookno() == "")
				break;
			this->ListInsert_B(e);   //插入书 
		}
		INFILE.close();
		cout << "图书信息载入成功\n";
	}
	return;
}

void BookSet::Output_Book(int pos)    //从第pos本开始输出以后的所有图书信息
{
	int i;
	Book e;
	if (pos > this->ListLength_B())
	{
		cout << "图书超量!\n";
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
			pressanykey(1);    //20行一断
			system("CLS");
			//if (iter < this->end())
				//cout << setw(6) << "书号" << setw(20) << "书名" << setw(8) << "作者" << setw(16) << "出版社" << setw(9) << "总存货量" << setw(9) << "能借量" << setw(10) << "出版日期" << endl;
		}
	}
	cout << endl;
}

void BookSet::Append_book(string filename)   //批量增加图书
{
	int k;
	//string filename;
	//cout << "**********新加入一批新书**********\n";
	//cout << "输入导入新书文件名:";
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
			e.setborrow(0);   //初始化新书借书量
			INFILE >> temp;
			e.setday(temp);
			if (e.getbookno() == "")
				break;
			this->ListInsert_B(e);
		}
		INFILE.close();
		//cout << "**********新加入以下一批新书 请核对**********\n";
		this->Output_Book(k + 1);
	}
	//else
		//cout << "没有找到该文件!\n";
}

void BookSet::book_manage_append()   //图书增加处理
{
	char a;
	Book e;
	while ((a = book_append_screen()) != '0')
		switch (a)
		{
		case'1':                   //只加一本书
			cout << "请输入单本新书的信息:\n";
			cin >> e;
			e.setborrow(0);   //初始化借书量
			this->ListInsert_B(e);   //加在末尾
			break;
		case'2':                  //从文件中增加一批书
			this->Append_book("");
			break;
		}
	return;
}

void BookSet::book_search_char(string info, int(Book::* f)(string))    //查询图书信息
{     //输入书名或部分,输出所有包含info的书籍
	int i, count = 0;
	int flag = 0;
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);           //提出每一本书籍数据
		if ((e.*f)(info))            //查找含info的书籍
		{
			count++;       //找到则数量加1
			if (!flag)         //flag标志 每一断的第一本书输出标头 
			{
				//cout << setw(6) << "书号" << setw(10) << "书名" << setw(8) << "作者" << setw(10) << "出版社" << setw(9) << "总存货量" << setw(9) << "能借量" << setw(10) << "出版日期" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10) << e.getpubday() << endl;
			if (count % 20 == 0)       //每20本  断开一次
			{
				pressanykey(1); flag = 0;
			}
		}
	}
	if (count)
		cout << "\n共找到" << count << "本书\n";
	else
		cout << "\n没能找到符合条件的书籍!\n";
	return;
}

void BookSet::book_search_have()         //查询还有多少书可借 
{
	int i, count = 0;
	int flag = 0;    //标头标志
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);        //提出所有书籍
		if (e.gettotalnum() - e.getborrownum() > 0)      //剩余书籍一本以上
		{
			count++;            //剩余数量加1 
			if (!flag)
			{
				//cout << setw(6) << "书号" << setw(30) << "书名" << setw(8) << "作者" << setw(20) << "出版社" << setw(4) << "总存货量" << setw(4) << "能借量" << setw(10) << "出版日期" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10) << e.getpubday() << endl;
			if (count % 20 == 0)       //每20本  断开一次
			{
				pressanykey(1); flag = 0;
			}
		}

	}
	if (count)
		cout << "\n共找到" << count << "本书\n";
	else
		cout << "\n没能找到符合条件的书籍!\n";
	return;
}

void BookSet::book_search_date(int year, int month)
{  //根据出版年月查询书籍 
	int i, count = 0;
	int flag = 0;
	Book e;
	for (i = 1; i <= this->ListLength_B(); i++)
	{
		this->GetElem_B(i, e);          //提出每一本书籍信息
		if (e.getpubday().getyear() == year && e.getpubday().getmonth() == month)    //与所输年月完全一致
		{
			count++;
			if (!flag)
			{
				//cout << setw(6) << "书号" << setw(30) << "书名" << setw(8) << "作者" << setw(20) << "出版社" << setw(4) << "总存货量" << setw(4) << "能借量" << setw(10) << "出版日期" << endl;
				flag = 1;
			}
			cout << setw(6) << e.getbookno() << setw(30) << e.getbookname() << setw(8) << e.getauthor() << setw(20) << e.getpublisher() << setw(4) << e.gettotalnum() << setw(4) << e.gettotalnum() - e.getborrownum() << setw(10);
			cout << e.getpubday() << endl;
			if (count % 20 == 0)       //每20本  断开一次
			{
				pressanykey(1); flag = 0;
			}
		}
	}
	if (count)
		cout << "\n共找到" << count << "本书\n";
	else
		cout << "\n没能找到符合条件的书籍!\n";
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
		case'1':cout << "按出版社查询书籍，请输入相关出版社名称:";
			cin >> infor;
			cout << endl;
			f = &Book::index_publisher;                 //index_publisher(e,infor)
			this->book_search_char(infor, f);
			break;
		case'2':cout << "按书名查询书籍,请输入书名:";
			cin >> infor;
			cout << endl;
			f = &Book::index_bookname;
			this->book_search_char(infor, f); break;
		case'3':cout << "按作者姓名查询书籍,请输入作者姓名:";
			cin >> infor;
			cout << endl;
			f = &Book::index_author;
			this->book_search_char(infor, f); break;
		case'4':cout << "按出版时间查询书籍,请输入出版年月:";
			cin >> year >> month;
			cout << endl;
			this->book_search_date(year, month);	break;
		case'5':cout << "按书号查询书籍,请输入书号:";
			cin >> infor;
			cout << endl;
			f = &Book::index_bookno;
			this->book_search_char(infor, f); break;
		case'6':  //剩余可借阅图书数量
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
