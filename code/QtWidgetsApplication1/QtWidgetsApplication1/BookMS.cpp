#include "BookMS.h"
#include "ValidIn.h"
BookMS::BookMS(StudentSet* stuSet, QWidget *parent)
    : QMainWindow(parent)
{
    stu_Set = stuSet;
    ui.setupUi(this);
    //���ڱ���ѧ����Ϣ
    //ui.numberLineEdit->setText(stu_Set->front().getstuno().c_str());
    //ui.passwordLineEdit->setText(stu_Set->at(1).getstumobi().c_str());
	ui.passwordLineEdit->setEchoMode(QLineEdit::Password);

	
	QObject::connect(ui.loginButton, &QPushButton::clicked, this, &BookMS::loginStudent);
	QObject::connect(ui.loginButton, &QPushButton::clicked, this, &BookMS::loginAdmin);


}

BookMS::~BookMS()
{}

//��첢��������
bool BookMS::validateInput(QLineEdit* numLE, QLineEdit* pwdLE, Student& stu){
	QString numInput = numLE->text();
	QString pwdInput = pwdLE->text();

	for (auto student : *stu_Set) {

		if (isLogin(numInput, pwdInput, student))
		{
			numLE->setStyleSheet("");
			pwdLE->setStyleSheet("");
			stu = student;
			return true;
		}
	}
	pwdLE->setStyleSheet("QLineEdit { background-color: #f65555;}");
	QMessageBox msgBox;
	QString str = QString::fromLocal8Bit(string("�������"));
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowTitle(QString::fromLocal8Bit(string("����")));
	msgBox.setText(str);
	msgBox.resize(900, 900); // ���ù̶���С

	msgBox.exec();
	return false;
}
//��첢��������
bool BookMS::validateAdminInput(QLineEdit* numLE, QLineEdit* pwdLE) {
	QString numInput = numLE->text();
	QString pwdInput = pwdLE->text();


	if (isAdminLogin(numInput, pwdInput))
	{
		numLE->setStyleSheet("");
		pwdLE->setStyleSheet("");
		return true;
	}
	pwdLE->setStyleSheet("QLineEdit { background-color: #f65555;}");
	QMessageBox msgBox;
	QString str = QString::fromLocal8Bit(string("�������"));
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowTitle(QString::fromLocal8Bit(string("����")));
	msgBox.setText(str);
	msgBox.resize(900, 900); // ���ù̶���С

	msgBox.exec();
	return false;
}
void BookMS::loginStudent() {
	Student t_stu;
	BookSet book;   //�鼮˳��� 
	book.OpenBookList();
	SBList borrow;   //������������ 
	borrow.begin_borrow();
	borrow.OpenBorrowList();
	stu_Set->OpenStuList();
	if (ui.stuButton->isChecked()) {
		if (validateInput(ui.numberLineEdit, ui.passwordLineEdit, t_stu))//��֤�˺�����
		{
			//������߽���
			
			Student_InfoDialog* stu_Info = new Student_InfoDialog(&t_stu, &book ,&borrow, this);
			stu_Info->exec();
		}


	}
}
void BookMS::loginAdmin() {


	if (ui.adminButton->isChecked()) {
		if (validateAdminInput(ui.numberLineEdit, ui.passwordLineEdit))//��֤�˺�����
		//if(true)
		{
			BookSet book;   //�鼮˳��� 
			StudentSet stu_set;
			stu_set.OpenStuList();
			book.OpenBookList();
			Admin_InfoDialog* admin_Info = new Admin_InfoDialog(this);
			admin_Info->exec();
		}
		//�������Ա����
	}
}
void BookMS::updateStuRadio() {
	if (!ui.stuButton->isChecked())
	{
		ui.stuButton->setChecked(true);
	}
	return;

}
