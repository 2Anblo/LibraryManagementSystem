#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookMS.h"
#include "StudentSet.h"
#include <QMessageBox>
#include "Student_InfoWidget.h"
#include "Student_InfoDialog.h"
#include "Admin_InfoDialog.h"


class BookMS : public QMainWindow
{
    Q_OBJECT

public:
    BookMS(StudentSet* stuSet, QWidget *parent = nullptr);
    ~BookMS();
    StudentSet* stu_Set;
    bool validateInput(QLineEdit* numLE, QLineEdit* pwdLE, Student& stu);
    bool validateAdminInput(QLineEdit* numLE, QLineEdit* pwdLE);
public slots:
    void loginStudent();
    void loginAdmin();
    void updateStuRadio();

private:
    Ui::BookMSClass ui;
};
