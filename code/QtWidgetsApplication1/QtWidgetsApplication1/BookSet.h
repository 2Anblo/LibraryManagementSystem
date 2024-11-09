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

	void OpenBookList();  //载入TXT的图书信息

	void Output_Book(int pos = 0);    //从第pos本开始输出以后的所有图书信息

	void Append_book(string filename);   //批量增加图书

	void book_manage_append();   //图书增加处理

	void book_search_char(string info, int(Book::* f)(string));    //查询图书信息


	void book_search_have();         //查询还有多少书可借 


	void book_search_date(int year, int month);


	void book_manage_search();

	void writeToFile(const std::string& filename);

};

