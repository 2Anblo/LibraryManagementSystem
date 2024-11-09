# pragma once
# include "Book.h"
#include "PreDefination.h"


class BookSet;

void pressanykey(int a);
char book_search_screen(void);
char book_append_screen(void);
char book_manager_screen(void);
void book_manager(BookSet& b);

class BookSet :public vector < Book >
{
public:
	//BookSet();
	//virtual ~BookSet();
	void returnBook(string bookNo);

	void borrowBook(string bookNo);

	int ListLength_B();

	Status ListInsert_B(Book e);

	Status LocateAllElem_B(Book e, Status(*compare)(Book, Book), int* find);

	Status GetElem_B(int i, Book& e);

	Status SetElem_B(int i, Book e);

	void OpenBookList();  //����TXT��ͼ����Ϣ

	void Output_Book(int pos = 0);    //�ӵ�pos����ʼ����Ժ������ͼ����Ϣ

	void Append_book(string filename);   //��������ͼ��

	void book_manage_append();   //ͼ�����Ӵ���

	void book_search_char(string info, int(Book::* f)(string));    //��ѯͼ����Ϣ


	void book_search_have();         //��ѯ���ж�����ɽ� 


	void book_search_date(int year, int month);


	void book_manage_search();

	void writeToFile(const std::string& filename);

};

