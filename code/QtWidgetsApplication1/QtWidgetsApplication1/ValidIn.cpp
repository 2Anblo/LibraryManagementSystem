#include "ValidIn.h"
#include <QDate>
void getDate(QString id, QDate& date, int& sex) {
    //根据身份证得到性别和出身日期
    //出生日期的格式为yyyy\mm\dd
    //sex=0为男性，sex=1为女性

    // Extract the birthdate
    QString birthYear = id.mid(6, 4);
    QString birthMonth = id.mid(10, 2);
    QString birthDay = id.mid(12, 2);
    date = QDate(birthYear.toInt(), birthMonth.toInt(), birthDay.toInt());

    // Determine the gender
    int genderDigit = id.mid(16, 1).toInt();
    sex = (genderDigit % 2 == 0) ? 1 : 0; // 0 for male, 1 for female
}
bool StringLen(QString str, int len, int option) {
    int strLen = str.size(); // 获取字符串长度

    switch (option) {
    case EQUE:
        return strLen == len;
    case GREATER:
        return strLen > len;
    case LESS:
        return strLen < len;
    default:
        return false; // 无效的option
    }
}
bool numberLen(QString str, int len, int option) {
    // 先检查str是否全是数字或'x'
    for (int i = 0; i < str.size(); ++i) {
        QChar ch = str[i];
        if (!ch.isDigit()) {
            return false;
        }
    }

    // 获取字符串长度
    int strLen = str.size();

    // 根据option进行长度比较
    switch (option) {
    case EQUE:
        return strLen == len;
    case GREATER:
        return strLen > len;
    case LESS:
        return strLen < len;
    default:
        return false; // 无效的option
    }
}
bool isid(QString str) {
    // 检查长度是否为15或18
    int length = str.size();
    if (length != 15 && length != 18) {
        return false;
    }

    // 检查前17位是否全为数字（对于18位身份证）
    for (int i = 0; i < (length == 18 ? 17 : 15); ++i) {
        if (!str[i].isDigit()) {
            return false;
        }
    }

    // 检查最后一位（如果是18位身份证）
    if (length == 18) {
        QChar lastChar = str[17];
        if (!lastChar.isDigit() && lastChar != 'x' && lastChar != 'X') {
            return false;
        }
    }

    // 如果通过以上检查，认为是有效的身份证号
    return true;
}
bool isLogin(QString account, QString pwd, Student stu) {


    //获取手机号后六位
    string lastsix = stu.getstumobi().substr(stu.getstumobi().size() - 6);
    //设定Ctsg前缀
    string prefix = "Ctsg";
    //组成密码字符串
    string stu_pwd = prefix + lastsix;
    if (stu.getstuno().c_str() == account.toLocal8Bit()&& stu_pwd.c_str() == pwd.toLocal8Bit())
    {
        return true;
    }
    return false;
}
bool isAdminLogin(QString account, QString pwd) {


    string admin_account = "admin";
    string admin_pwd = "CNU123";
    if (admin_account.c_str() == account.toLocal8Bit() && admin_pwd.c_str() == pwd.toLocal8Bit())
    {
        return true;
    }
    return false;
}