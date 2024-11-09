#include "cell_personInfo.h"

cell_personInfo::cell_personInfo(Student* m_stu, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	stu = m_stu;
	ui.numLE->setText(QString::fromLocal8Bit(stu->getstuno()));
	ui.nameLE->setText(QString::fromLocal8Bit(stu->getstuname()));
	ui.classLE->setText(QString::fromLocal8Bit(stu->getstuclass()));
	ui.majorLE->setText(QString::fromLocal8Bit(stu->getstumajor()));
	ui.phoneLE->setText(QString::fromLocal8Bit(stu->getstumobi()));
	ui.numLE->setDisabled(true);
	ui.nameLE->setDisabled(true);
	ui.classLE->setDisabled(true);
	ui.majorLE->setDisabled(true);
	ui.phoneLE->setDisabled(true);

	// ׼��ͼƬ�б�
	QStringList images = { ":/Character/goku.png", ":/Character/kirby.png", ":/Character/patrick.png",":/Character/hachi.png",":/Character/wusachi.png",
						  ":/Character/spiderman.png", ":/Character/ykirby.png", ":/Character/mario.png",
						  ":/Character/ironman.png", ":/Character/capitaina.png",":/Character/zwz.png"};

	// ��ȡѧ�Ų���ȡ�����λ
	QString studentNumber = QString::fromLocal8Bit(stu->getstuno());
	QString lastFourDigits = studentNumber.right(4);

	// �������λת��Ϊ����
	bool ok;
	int number = lastFourDigits.toInt(&ok);
	if (!ok) {
		qDebug() << "Failed to convert last four digits to integer.";
		number = 0; // ���ת��ʧ�ܣ�ʹ��Ĭ��ֵ0
	}

	// ��9ȡ�������õ�����
	int randomIndex = number % 11;

	// ���ͼƬ�Ƿ���ȷ����
	QString selectedImage = images.at(randomIndex);
	qDebug() << randomIndex;
	QPixmap pixmap(selectedImage);
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image:" << selectedImage;
	}
	else {
		// ����QLabel��pixmap
		ui.imageLabel->setPixmap(pixmap);
	}
}

cell_personInfo::~cell_personInfo()
{}
