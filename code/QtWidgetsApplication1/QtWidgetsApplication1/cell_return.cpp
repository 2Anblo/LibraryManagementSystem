#include "cell_return.h"

cell_return::cell_return(Student* m_stu, SBList* list, BookSet* set, QWidget *parent)
	: QWidget(parent)
{
	r_list = list;
	r_stu = m_stu;
	b_set = set;
	ui.setupUi(this);
	ui.returnTable->setContextMenuPolicy(Qt::CustomContextMenu);

	returnTableSetting();
	imageCarousel();

}

cell_return::~cell_return()
{}

void cell_return::imageCarousel() {
	timer = new QTimer(this);

	imageList = { ":/background/CNUlib.png",":/background/CNUcenter.png", ":/background/CNUeast.png", ":/background/CNUeast2.png", ":/background/CNUorg.png" };
	currentImageIndex = 0;
	ui.imageLabel->setPixmap(QPixmap(imageList[currentImageIndex]));

	connect(timer, &QTimer::timeout, this, &cell_return::nextImage);
	timer->start(3000); // ÿ3���л�һ��ͼƬ
}

void cell_return::nextImage(){
	++currentImageIndex;
	if (currentImageIndex >= imageList.size()) {
		currentImageIndex = 0;
	}
	ui.imageLabel->setPixmap(QPixmap(imageList[currentImageIndex]));
}

void cell_return::returnTableSetting() {
	ui.returnTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.returnTable->setColumnCount(5);
	ui.returnTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("������") << QString::fromLocal8Bit("�鼮���") 
															<< QString::fromLocal8Bit("����")
															<< QString::fromLocal8Bit("��������") << QString::fromLocal8Bit("��������")); //��������

	QHeaderView* header = ui.returnTable->horizontalHeader();
	refreshTable();
	QFont font = ui.returnTable->horizontalHeader()->font();
	font.setBold(true);
	ui.returnTable->horizontalHeader()->setFont(font);

	ui.returnTable->resizeColumnsToContents();

	// �����ض��еĿ��
	ui.returnTable->setColumnWidth(0, 100);  // ��һ�п������Ϊ100px
	ui.returnTable->setColumnWidth(1, 80);  // �ڶ��п������Ϊ80px
	ui.returnTable->setColumnWidth(3, 150); // �����п������Ϊ150px
	ui.returnTable->setColumnWidth(4, 150); // �����п������Ϊ150px
	ui.returnTable->setColumnWidth(2, 721-480); 

	


}
void cell_return::refreshTable() {
	//����ʽ����������
	BorrowInfoSet r_borrowSet;
	if (r_list->StuWhetherIn(r_stu->getstuno())) {

		r_list->getSBList();
		for (auto i : r_list->getSBList())
		{
			if (i.getstudentno() == r_stu->getstuno()) {
				r_borrowSet = i.getblist();
				int row;
				ui.returnTable->setRowCount(0);
				ui.returnTable->setRowCount(r_borrowSet.size());
				BorrowInfoSet::iterator it;
				//����Ϣ������
				for (it = r_borrowSet.begin(), row = 0; it != r_borrowSet.end(); it++, row++) {
					int col = 0;
					ui.returnTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(r_stu->getstuname())));
					ui.returnTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookno())));
					ui.returnTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookname())));
					ui.returnTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getborrowday().dateFormat())));
					ui.returnTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getborrowday().overdueFormat())));

					ui.returnTable->item(row ,4)->setTextAlignment(Qt::AlignCenter);
					ui.returnTable->item(row ,2)->setTextAlignment(Qt::AlignCenter);
					ui.returnTable->item(row, 0)->setTextAlignment(Qt::AlignCenter);
					ui.returnTable->item(row ,1)->setTextAlignment(Qt::AlignCenter);
					ui.returnTable->item(row, 3)->setTextAlignment(Qt::AlignCenter);


					for (int col = 0; col < 5; ++col) {

						QTableWidgetItem* pItem = ui.returnTable->item(row, col);
						pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));

					}


				}
				return;
			}
		}
	}
	else
	{
		ui.returnTable->setRowCount(0);
	}

}

void cell_return::onRightClickShowMenu(QPoint pos) {
	QMenu contextMenu;
	QAction* returnBookAction;



	QTableWidgetItem* item = ui.returnTable->itemAt(pos);
	if (item == nullptr)return;

	QString m_BID;
	int row = item->row();
	QTableWidgetItem* firstItem = item->tableWidget()->item(row, 1);
	if (firstItem) {
		m_BID = firstItem->text();
	}

	returnBookAction = new QAction(QString().fromLocal8Bit("����"), &contextMenu);


	returnBookAction->setIcon(QIcon(":/Book/book-open.svg"));

	connect(returnBookAction, &QAction::triggered, [=]() {onReturnBookAction(m_BID); });

	contextMenu.addAction(returnBookAction);


	contextMenu.exec(ui.returnTable->mapToGlobal(pos));
}
void cell_return::onReturnBookAction(const QString& m_BID) {
	Book book;
	book.setbookno(m_BID.toStdString());
	if (!b_set->empty())
	{
		auto it = std::find(b_set->begin(), b_set->end(), book);
	
			// ��������ʾ PersonInfIODlg ����

			it->setborrow(it->getborrownum() - 1);
			BorrowInfo newBorrow;
			newBorrow.setbookname(it->getbookname());
			newBorrow.setbookno(it->getbookno());
			newBorrow.setborrowday(Get_Sys_Time());
			if (r_list->StuWhetherIn(r_stu->getstuno()))
			{
				r_list->returnbook(r_stu->getstuno(), book.getbookno());
				b_set->returnBook(r_stu->getstuno());
			
			}
			b_set->writeToFile("book.txt");
			r_list->WriteToFile();
			QMessageBox msgBox;
			QString str = QString::fromLocal8Bit(string("����ɹ���"));
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
			msgBox.setText(str);
			msgBox.resize(900, 900); // ���ù̶���С

			msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		QString str = QString::fromLocal8Bit(string("����ʧ�ܣ�����"));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle(QString::fromLocal8Bit(string("����״̬")));
		msgBox.setText(str);
		msgBox.resize(900, 900); // ���ù̶���С

		msgBox.exec();
	}
		

	refreshTable();
}