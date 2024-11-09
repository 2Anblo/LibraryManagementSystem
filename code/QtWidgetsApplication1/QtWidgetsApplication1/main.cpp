//#include "vld.h"

#include "BookMS.h"
#include <QtWidgets/QApplication>
#include "PreDefination.h"
#include "StudentSet.h"
#include "SBList.h"
#include "RelationshipSet.h"
#include "BookSet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	StudentSet stu;    //学生顺序表 
	BookSet book;   //书籍顺序表 

	RelationshipSet queue; //存放预约队列 	
	stu.OpenStuList();   //载入学生信息
	book.OpenBookList();

	BookMS w(&stu);
    w.show();

    return a.exec();

}
