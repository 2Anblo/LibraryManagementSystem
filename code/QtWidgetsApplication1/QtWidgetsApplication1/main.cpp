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

	StudentSet stu;    //ѧ��˳��� 
	BookSet book;   //�鼮˳��� 

	RelationshipSet queue; //���ԤԼ���� 	
	stu.OpenStuList();   //����ѧ����Ϣ
	book.OpenBookList();

	BookMS w(&stu);
    w.show();

    return a.exec();

}
