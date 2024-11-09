#include "ValidIn.h"
#include <QDate>
void getDate(QString id, QDate& date, int& sex) {
    //�������֤�õ��Ա�ͳ�������
    //�������ڵĸ�ʽΪyyyy\mm\dd
    //sex=0Ϊ���ԣ�sex=1ΪŮ��

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
    int strLen = str.size(); // ��ȡ�ַ�������

    switch (option) {
    case EQUE:
        return strLen == len;
    case GREATER:
        return strLen > len;
    case LESS:
        return strLen < len;
    default:
        return false; // ��Ч��option
    }
}
bool numberLen(QString str, int len, int option) {
    // �ȼ��str�Ƿ�ȫ�����ֻ�'x'
    for (int i = 0; i < str.size(); ++i) {
        QChar ch = str[i];
        if (!ch.isDigit()) {
            return false;
        }
    }

    // ��ȡ�ַ�������
    int strLen = str.size();

    // ����option���г��ȱȽ�
    switch (option) {
    case EQUE:
        return strLen == len;
    case GREATER:
        return strLen > len;
    case LESS:
        return strLen < len;
    default:
        return false; // ��Ч��option
    }
}
bool isid(QString str) {
    // ��鳤���Ƿ�Ϊ15��18
    int length = str.size();
    if (length != 15 && length != 18) {
        return false;
    }

    // ���ǰ17λ�Ƿ�ȫΪ���֣�����18λ���֤��
    for (int i = 0; i < (length == 18 ? 17 : 15); ++i) {
        if (!str[i].isDigit()) {
            return false;
        }
    }

    // ������һλ�������18λ���֤��
    if (length == 18) {
        QChar lastChar = str[17];
        if (!lastChar.isDigit() && lastChar != 'x' && lastChar != 'X') {
            return false;
        }
    }

    // ���ͨ�����ϼ�飬��Ϊ����Ч�����֤��
    return true;
}
bool isLogin(QString account, QString pwd, Student stu) {


    //��ȡ�ֻ��ź���λ
    string lastsix = stu.getstumobi().substr(stu.getstumobi().size() - 6);
    //�趨Ctsgǰ׺
    string prefix = "Ctsg";
    //��������ַ���
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