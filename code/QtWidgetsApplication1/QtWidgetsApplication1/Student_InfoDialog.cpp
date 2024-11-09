#include "Student_InfoDialog.h"
#include "SBList.h"

Student_InfoDialog::Student_InfoDialog(Student* m_stu, BookSet* m_book,SBList* m_borrow, QWidget *parent)
	: QDialog(parent)
	,m_borrowPage(nullptr)
	,m_returnPage(nullptr)
	,m_personInfoPage(nullptr)
	,m_recommendPage(nullptr)

{


	ui.setupUi(this);

	stu = m_stu;
	book = m_book;
	borrow = m_borrow;
	initPage();
}

Student_InfoDialog::~Student_InfoDialog()
{}
void Student_InfoDialog::initPage()
{

	m_borrowPage = new cell_borrow(stu, book, borrow, this);
	m_returnPage = new cell_return(stu, borrow, book, this);
	m_personInfoPage = new cell_personInfo(stu, this);
	m_recommendPage = new cell_recommend(borrow, book, this);
	ui.stackedWidget->addWidget(m_borrowPage);
	ui.stackedWidget->addWidget(m_returnPage);
	ui.stackedWidget->addWidget(m_personInfoPage);
	ui.stackedWidget->addWidget(m_recommendPage);
	ui.stackedWidget->setCurrentIndex(0);

	auto l = ui.tool->children();
	for (auto it : l)
	{
		if (it->objectName().contains("Btn")) {
			connect(static_cast<QAbstractButton*>(it), &QAbstractButton::clicked, this, &Student_InfoDialog::dealMenu);
		}
	}
}
void Student_InfoDialog::dealMenu()
{
	auto str = sender()->objectName();

	do
	{
		if ("bookTBtn" == str)
		{
			m_borrowPage->refreshTable(book);
			ui.stackedWidget->setCurrentIndex(0);
			break;
		}

		if ("borrowTBtn" == str)
		{
			m_returnPage->refreshTable();
			ui.stackedWidget->setCurrentIndex(1);
			break;
		}

		if ("personTBtn" == str)
		{
			ui.stackedWidget->setCurrentIndex(2);
			break;
		}
		if("recommendTBtn" == str)
		{
			m_recommendPage->refreshTable();
			ui.stackedWidget->setCurrentIndex(3);
			break;
		}
	} while (false);
}