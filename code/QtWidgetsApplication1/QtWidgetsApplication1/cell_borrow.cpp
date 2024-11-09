#include "cell_borrow.h"

cell_borrow::cell_borrow(Student* stu, BookSet* set, SBList* borrow, QWidget *parent)
	: QWidget(parent)
{
	b_stu = stu;
	b_set = set;
	b_borrow = borrow;
	ui.setupUi(this);
	ui.borrowTable->setContextMenuPolicy(Qt::CustomContextMenu);

	// 创建一个QTimer来定时更新时间
	timer = new QTimer(this);
	timer->setInterval(1000); // 设置定时器间隔为1000毫秒（1秒）

	// 连接定时器的timeout信号到更新时间的槽函数
	connect(timer, &QTimer::timeout, this, &cell_borrow::updateTime);

	// 启动定时器
	timer->start();

	// 更新时间标签以显示当前时间
	updateTime();
	borrowTableSetting();


}

cell_borrow::~cell_borrow()
{}

void cell_borrow::updateTime() {
	// 设置时区为中国时区（中国标准时间，CST）
	QDateTime dateTime = QDateTime::currentDateTimeUtc().addSecs(8 * 3600);
	QString currentTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");
	ui.timeLabel->setText(currentTime);
}

void cell_borrow::refreshTable(BookSet* set) {
	int i;
	ui.borrowTable->setRowCount(0);
	ui.borrowTable->setRowCount(set->size());
	BookSet::iterator it;
	//将信息插入表格
	for (it = set->begin(), i = 0; it != set->end(); it++, i++) {
		int col = 0;
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromStdString(it->getbookno())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookname())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getauthor())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpublisher())));
		
		//设置当前存量
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->gettotalnum()- it->getborrownum())));

		//ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->gettotalnum())));
		//ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::number(it->getborrownum())));
		ui.borrowTable->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpubday().dateFormat())));

		//居中设置存量,发售日期,书名
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
	//表格格式和内容设置
	ui.borrowTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.borrowTable->setColumnCount(6);
	ui.borrowTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("书籍编号") << QString::fromLocal8Bit("书名")
											<< QString::fromLocal8Bit("作者") << QString::fromLocal8Bit("出版公司") << QString::fromLocal8Bit("当前存量")
											 << QString::fromLocal8Bit("发售日期"));

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
			// 创建并显示 PersonInfIODlg 界面
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
						QString str = QString::fromLocal8Bit(string("借阅成功！"));
						msgBox.setIcon(QMessageBox::Warning);
						msgBox.setWindowTitle(QString::fromLocal8Bit(string("借阅状态")));
						msgBox.setText(str);
						msgBox.resize(900, 900); // 设置固定大小

						msgBox.exec();
					}

					else
					{
						QMessageBox msgBox1;
						QString str = QString::fromLocal8Bit(string("借阅失败！您的借阅数量已达上限！"));
						msgBox1.setIcon(QMessageBox::Warning);
						msgBox1.setWindowTitle(QString::fromLocal8Bit(string("借阅状态")));
						msgBox1.setText(str);
						msgBox1.resize(900, 900); // 设置固定大小

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
						QString str = QString::fromLocal8Bit(string("借阅成功！"));
						msgBox.setIcon(QMessageBox::Warning);
						msgBox.setWindowTitle(QString::fromLocal8Bit(string("借阅状态")));
						msgBox.setText(str);
						msgBox.resize(900, 900); // 设置固定大小

						msgBox.exec();
					}
					else
					{
						QMessageBox msgBox1;
						QString str = QString::fromLocal8Bit(string("借阅失败！您的借阅数量已达上限！"));
						msgBox1.setIcon(QMessageBox::Warning);
						msgBox1.setWindowTitle(QString::fromLocal8Bit(string("借阅状态")));
						msgBox1.setText(str);
						msgBox1.resize(900, 900); // 设置固定大小

						msgBox1.exec();
					}
				}
				
			}
			else
			{
				QMessageBox msgBox;
				QString str = QString::fromLocal8Bit(string("借阅失败！馆内该书已全部借出！"));
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle(QString::fromLocal8Bit(string("借阅状态")));
				msgBox.setText(str);
				msgBox.resize(900, 900); // 设置固定大小

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

	borrowBookAction = new QAction(QString().fromLocal8Bit("借书"), &contextMenu);

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
					it->getbookno().find(searchText) != std::string::npos ||  // 使用std::to_string进行转换
					it->getpubday().dateFormat().find(searchText) != std::string::npos ||
					it->getpublisher().find(searchText) != std::string::npos ||
					std::to_string(it->gettotalnum()-it->getborrownum()).find(searchText) != std::string::npos;  // 使用std::to_string进行转换
				// 如果 searchText 被找到，则添加到搜索集合中
				if (isFound) {
					searchedSet.push_back(*it);
				}

			}
			catch (...) {}
		}

	}
	
	refreshTable(&searchedSet);
}