# pragma once
# include "Date.h"
#include "PreDefination.h"


class BorrowInfo    //������Ϣ
{
private:
	string bookno;    //���
	Date borrowday;     //��������
	
	string bookname;  //����
public:
    // �������
	void setbookno(string bno);
    // ���ý�������
	void setborrowday(Date d);
    // ��ȡ���
	string getbookno();
    // ��ȡ��������
	Date getborrowday();

	friend std::istream& operator>>(std::istream& is, BorrowInfo& bi);   //����������������
	friend std::ostream& operator<<(std::ostream& os, BorrowInfo& bi);

    // ��������
	void setbookname(string bname);
    // ��ȡ����
	string getbookname();

};
