#pragma once
#include <QString>
#include <QDate>
#include "Student.h"

#define EQUE 0
#define GREATER 1
#define LESS 2

void getDate(QString id, QDate& date, int& sex);
bool StringLen(QString str, int len, int option);
bool numberLen(QString str, int len, int option);
bool isid(QString str);
bool isLogin(QString account, QString pwd, Student stu);
bool isAdminLogin(QString account, QString pwd);