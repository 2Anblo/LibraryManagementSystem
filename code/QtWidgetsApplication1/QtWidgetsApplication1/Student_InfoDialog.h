#pragma once

#include <QDialog>
#include "ui_Student_InfoDialog.h"
#include "cell_personInfo.h"
#include "cell_return.h"
#include "cell_borrow.h"
#include "cell_recommend.h"
#include "Student.h"

class Student_InfoDialog : public QDialog
{
	Q_OBJECT

public:
	Student_InfoDialog(Student* m_stu, BookSet* m_book,SBList* m_borrow, QWidget *parent = nullptr);
	~Student_InfoDialog();
	// ��ʼ��ҳ�棬���ø�����ҳ��ĳ�ʼ״̬
	void initPage();
public slots:
    // ����˵������������û���ѡ�����������ʾ
	void dealMenu();
private:
	Ui::Student_InfoDialogClass ui;// �û���������ã��� Qt �� UIC �����Զ����ɺ͹���
	// ѧ������ҳ��
	cell_borrow* m_borrowPage;
    // ѧ���黹ҳ��
	cell_return* m_returnPage;
    // ѧ��������Ϣҳ��
	cell_personInfo* m_personInfoPage;
    // �Ƽ��鼮ҳ��
	cell_recommend* m_recommendPage;
    // ָ��ǰ������ѧ������
	Student* stu;
    // ָ��ǰ�������鼮����
	BookSet* book;
    // ָ��ǰ������Ϣ��������
	SBList* borrow;   

};
