#include "cell_borrow.h"

cell_borrow::cell_borrow(Student* stu, BookSet* set, SBList* borrow, QWidget *parent)
	: QWidget(parent)
{
	b_stu = stu;
	b_set = set;
	b_borrow = borrow;
	ui.setupUi(this);
	ui.borrowTable->setContextMenuPolicy(Qt::CustomContextMenu);

	// ����һ��QTimer����ʱ����ʱ��
	timer = new QTimer(this);
	timer->setInterval(1000); // ���ö�ʱ�����Ϊ1000���루1�룩

	// ���Ӷ�ʱ����timeout�źŵ�����ʱ��Ĳۺ���
	connect(timer, &QTimer::timeout, this, &cell_borrow::updateTime);

	// ������ʱ��
	timer->start();

	// ����ʱ���ǩ����ʾ��ǰʱ��
	updateTime();
	borrowTableSetting();


}

cell_borrow::~cell_borrow()
{}

void cell_borrow::updateTime() {
	// ����ʱ��Ϊ�й�ʱ�����й���׼ʱ�䣬CST��
	QDateTime dateTime = QDateTime::currentDateTimeUtc().addSecs(8 * 3600);
	QString currentTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");
	ui.timeLabel->setText(currentTime);
}

void cell_borrow::refreshTable(BookSet* set) {
	int i;
	ui.borrowTable->setRowCount(0);
	ui.borrowTable->setRowCount(set->size());
	BookSet::iterator it;
	//����Ϣ������
	for (it = set->begin(), i = 0; it != set->end(); it++, i++) {
		int col = 0;
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromStdString(it->getbookno())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookname())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getauthor())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpublisher())));
		
		//���õ�ǰ����
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->gettotalnum()- it->getborrownum())));

		//ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->gettotalnum())));
		//ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->getborrownum())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpubday().dateFormat())));

		//�������ô���,��������,����
		ui.borrowTable->item(i, 4)->setTextAlignment(Qt::AlignCenter);
		ui.borrowTable->item(i, 5)->setTextAlignment(Qt::AlignCenter);
		ui.borrowTable->item(i, 1)->setTextAlignment(Qt::AlignCenter);

		for (int col = 0; col < 6; ++col) {

			QTableWidgetItem* pItem = ui.borrowTable->item(i, col);
			pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));

		}

	}
}
void cell_borrow::borrowTableSetting() {
	//����ʽ����������
	ui.borrowTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.borrowTable->setColumnCount(6);
	ui.borrowTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("�鼮���") << QString::fromLocal8Bit("����")
											<< QString::fromLocal8Bit("����") << QString::fromLocal8Bit("���湫˾") << QString::fromLocal8Bit("��ǰ����")
											 << QString::fromLocal8Bit("��������"));

	QHeaderView* header = ui.borrowTable->horizontalHeader();
	refreshTable(b_set);

	QFont font = ui.borrowTable->horizontalHeader()->font();
	font.setBold(true);
	ui.borrowTable->horizontalHeader()->setFont(font);

	ui.borrowTable->resizeColumnsToContents();
	for (int i = 0; i < ui.borrowTable->columnCount(); i++) {
		int width = ui.borrowTable->columnWidth(i);
		ui.borrowTable->setColumnWidth(i, width + 50);
	}




}

void cell_borrow::onBorrowBookAction(const QString& m_BID) {

	Book book;
	book.setbookno(m_BID.toStdString());
	if (!b_set->empty())
	{
		auto it = std::find(b_set->begin(), b_set->end(), book);
		if (it != b_set->end()) {
			// ��������ʾ PersonInfIODlg ����
			Book m_book;


			if (it->getborrownum() < it->gettotalnum()) {
				it->setborrow(it->getborrownum()+1);
				BorrowInfo newBorrow;
				newBorrow.setbookname(it->getbookname());
				newBorrow.setbookno(it->getbookno());
				newBorrow.setborrowday(Get_Sys_Time());


				if (b_borrow->StuWhetherIn(b_stu->getstuno()))
				{
					if (b_borrow->bookLimit(b_stu->getstuno()))
					{
						b_borrow->addanewrelation(b_stu->getstuno(), newBorrow);
						b_borrow->WriteToFile();

						b_set->borrowBook(b_stu->getstuno());
						b_set->writeToFile("book.txt");
						QMessageBox msgBox;
						QString str = QString::fromLocal8Bit(string("���ĳɹ���"));
						msgBox.setIcon(QMessageBox::Warning);
						msgBox.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
						msgBox.setText(str);
						msgBox.resize(900, 900); // ���ù̶���С

						msgBox.exec();
					}

					else
					{
						QMessageBox msgBox1;
						QString str = QString::fromLocal8Bit(string("����ʧ�ܣ����Ľ��������Ѵ����ޣ�"));
						msgBox1.setIcon(QMessageBox::Warning);
						msgBox1.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
						msgBox1.setText(str);
						msgBox1.resize(900, 900); // ���ù̶���С

						msgBox1.exec();
					}
				}
				else
				{
					if (b_borrow->bookLimit(b_stu->getstuno()))
					{
						StudentNode newStudent;
						newStudent.setborrownum(0);
						newStudent.setstudentno(b_stu->getstuno());
						b_borrow->pushelem(newStudent);
						b_borrow->addanewrelation(b_stu->getstuno(), newBorrow);
						b_set->borrowBook(b_stu->getstuno());
						b_set->writeToFile("book.txt");
						b_borrow->WriteToFile();
						QMessageBox msgBox;
						QString str = QString::fromLocal8Bit(string("���ĳɹ���"));
						msgBox.setIcon(QMessageBox::Warning);
						msgBox.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
						msgBox.setText(str);
						msgBox.resize(900, 900); // ���ù̶���С

						msgBox.exec();
					}
					else
					{
						QMessageBox msgBox1;
						QString str = QString::fromLocal8Bit(string("����ʧ�ܣ����Ľ��������Ѵ����ޣ�"));
						msgBox1.setIcon(QMessageBox::Warning);
						msgBox1.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
						msgBox1.setText(str);
						msgBox1.resize(900, 900); // ���ù̶���С

						msgBox1.exec();
					}
				}
				
			}
			else
			{
				QMessageBox msgBox;
				QString str = QString::fromLocal8Bit(string("����ʧ�ܣ����ڸ�����ȫ�������"));
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
				msgBox.setText(str);
				msgBox.resize(900, 900); // ���ù̶���С

				msgBox.exec();
			}
		}
	}
	

	refreshTable(b_set);

}

void cell_borrow::onRightClickShowMenu(QPoint pos) {
	QMenu contextMenu;
	QAction* borrowBookAction;



	QTableWidgetItem* item = ui.borrowTable->itemAt(pos);
	if (item == nullptr)return;

	QString m_BID;
	int row = item->row();
	QTableWidgetItem* firstItem = item->tableWidget()->item(row, 0);
	if (firstItem) {
		m_BID = firstItem->text();
	}

	borrowBookAction = new QAction(QString().fromLocal8Bit("����"), &contextMenu);

	borrowBookAction->setIcon(QIcon(":/Book/book-open.svg"));

	connect(borrowBookAction, &QAction::triggered, [=]() {onBorrowBookAction(m_BID); });

	contextMenu.addAction(borrowBookAction);

	contextMenu.exec(ui.borrowTable->mapToGlobal(pos));
}

void cell_borrow::onSearchAction() {
	BookSet searchedSet;
	std::string searchText = ui.searchLE->text().toLocal8Bit().toStdString();
	BookSet::iterator it;
	if (searchText.empty()) {
		for (it = b_set->begin(); it != b_set->end(); it++)
		{
					searchedSet.push_back(*it);
		}
	}
	else
	{
		for (it = b_set->begin(); it != b_set->end(); it++)
		{
			try {


				bool isFound = it->getauthor().find(searchText) != std::string::npos ||
					it->getbookname().find(searchText) != std::string::npos ||
					it->getbookno().find(searchText) != std::string::npos ||  // ʹ��std::to_string����ת��
					it->getpubday().dateFormat().find(searchText) != std::string::npos ||
					it->getpublisher().find(searchText) != std::string::npos ||
					std::to_string(it->gettotalnum()-it->getborrownum()).find(searchText) != std::string::npos;  // ʹ��std::to_string����ת��
				// ��� searchText ���ҵ�������ӵ�����������
				if (isFound) {
					searchedSet.push_back(*it);
				}

			}
			catch (...) {}
		}

	}
	
	refreshTable(&searchedSet);
}