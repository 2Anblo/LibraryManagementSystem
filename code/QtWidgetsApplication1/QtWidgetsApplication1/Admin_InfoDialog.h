#pragma once

#include <QDialog>
#include "ui_Admin_InfoDialog.h"
#include "BookSet.h"
#include "StudentSet.h"

class Admin_InfoDialog : public QDialog
{
	Q_OBJECT

public:
	Admin_InfoDialog(QWidget* parent = nullptr);
	~Admin_InfoDialog();
	void set_TabelWghit();    // ����ͼ����Ľ���Ԫ��

	void set_TabelWghit_stu();    // ����ѧ�����Ľ���Ԫ��

	std::vector<QPushButton*> btn; //����ϵĿؼ�
	std::vector<QCheckBox*> mark; //����ϵ�ѡ�б��

	std::vector<QPushButton*> stu_btn;    // �洢ѧ������еİ�ť

	std::vector<QCheckBox*>stu_mark;    // �洢ѧ������еĸ�ѡ��

	void refreshTable(BookSet* set);    // ˢ���鼮��Ϣ�����ʾ�������鼮��

	void exchange_Set(const string str);
	int find_book_and_return_idx(Book* book);    // ���鼮���в���ָ���鼮������������

	int find_stu_and_return_idx(Student* stu);    // ��ѧ�����в���ָ��ѧ��������������

	//��ȫ����֤
	bool requireInt(const QString& str);// ��֤�ַ����Ƿ�Ϊ����
	bool isValidDateFormat(const QString& Qstr);// ��֤���ڸ�ʽ�Ƿ���Ч
	string getSafeString(const QTableWidgetItem* item);// �ӱ����л�ȡ��ȫ�ַ���
	bool isNumber(string str);// ����ַ����Ƿ�ȫ��Ϊ����
	bool isBooknoUnique(int i, QTableWidgetItem* item);// �������Ƿ�Ψһ
	bool isStunoUnique(int i, QTableWidgetItem* item);// ���ѧ���Ƿ�Ψһ
public slots:
    // ���õ�ǰҳ��
	void set_page(int page_name);
    // �����Ŀ���鼮���
	void add_item_to_TableWghit();
    // �ӱ���ȡ�鼮����
	Book* get_book_from_TableWghit(int i);
    // �������ı���е���Ŀ
	void save_or_change_for_TableWghit(int i);
    // ���鼮���ɾ����Ŀ
	void delete_book_from_TableWghit();
    // ȡ���鼮����е�ѡ����Ŀ
	void cancel_item_from_TableWghit();
    // ȫѡ��ȡ��ѡ��������Ŀ
	void choise_or_unchoise_all_item_from_TableWghit();
    // ���ļ�����鼮
	void add_book_from_file();

    // ִ���鼮��������
	void onSearchAction_book();
    // ִ��ѧ����������
	void onSearchAction_stu();

    // ˢ��ѧ����Ϣ���
	void refreshTable_stu(StudentSet* s_set);
    // �����Ŀ��ѧ�����
	void add_item_to_stu_TableWghit();
    // ��������ѧ������е���Ŀ
	void save_or_change_for_stu_TableWghit(int i);
    // ��ѧ�����ɾ����Ŀ
	void delete_book_from_stu_TableWghit();
    // ȫѡ��ȡ��ѡ������ѧ�������Ŀ
	void choise_or_unchoise_all_item_from_stu_TableWghit();
    // ��ѧ������ȡѧ������
	Student* get_student_from_stu_TableWghit(int i);
    // ���ļ����ѧ��
	void add_stu_from_file();

    // ��ʾ�Զ�����Ϣ��
	void showCustomMessageBox(const std::string& title, const std::string& message);
private:
	Ui::Admin_InfoDialogClass ui;// ����Ա�������
	BookSet* b_set;// ���鼮��
	StudentSet* s_set;// ��ѧ����
	BookSet* search_BookSet;  // ��������鼮��
	StudentSet* search_StuSet;  // �������ѧ����

	BookSet* current_BookSet;  // ��ǰ����鼮��
	StudentSet* current_StuSet;  // ��ǰ���ѧ����

};
