#include "cell_recommend.h"

cell_recommend::cell_recommend(SBList* list, BookSet* set, QWidget *parent)
	: QWidget(parent)
{
	r_list = list;
	b_set = set;
	ui.setupUi(this);

	recommendTableSetting();
}

cell_recommend::~cell_recommend()
{}
void cell_recommend::refreshTable() {
    // 表格格式和内容设置
    BorrowInfoSet r_borrowSet;
    std::map<std::string, int> booknoCount; // 用于存储bookno出现的次数

   
    for (auto i : r_list->getSBList()) {
        r_borrowSet = i.getblist();

        int row;

        BorrowInfoSet::iterator it;

        // 将信息插入表格
        for (it = r_borrowSet.begin(), row = 0; it != r_borrowSet.end(); it++, row++) {
            // 统计bookno出现的次数
            booknoCount[it->getbookno()]++;
        }
    }

    // 将map转换为vector，以便排序
    std::vector<std::pair<std::string, int>> booknoCountVec(booknoCount.begin(), booknoCount.end());

    // 根据出现次数降序排序
    std::sort(booknoCountVec.begin(), booknoCountVec.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });

    // 提取前5个
    std::vector<std::pair<std::string, int>> top5Booknos;
    if (booknoCountVec.size() > 5) {
        top5Booknos.assign(booknoCountVec.begin(), booknoCountVec.begin() + 5);
    }
    else {
        top5Booknos = booknoCountVec;
    }

   
    BookSet* recommendSet = new BookSet;
    for (const auto& pair : top5Booknos) {
        // 打印前5个bookno及其出现次数（仅用于调试）
        //qDebug() << "Book No:" << pair.first << ", Count:" << pair.second;
        for (auto it = b_set->begin(); it != b_set->end(); it++)
        {
            if (it->getbookno() == pair.first)
            {
                recommendSet->push_back(*it);
                break;
            }
        }
    }

 
    BookSet::iterator it;
    //将信息插入表格
    int row;
    ui.recommendTable->setRowCount(0);
    ui.recommendTable->setRowCount(recommendSet->size());
    int expectedRows = recommendSet->size();
    for (it = recommendSet->begin(), row = 0; it!=recommendSet->end(); it++, row++) {
        int col = 0;
           
            //★ QChar(0x2605)
            int count = booknoCount[it->getbookno()];
            QString stars;

            if (count == 5) {
                stars = QString(QChar(0x2605)).repeated(5);
            }
            else if (count == 4) {
                stars = QString(QChar(0x2605)).repeated(4);
            }
            else if (count == 3) {
                stars = QString(QChar(0x2605)).repeated(3);
            }
            else if (count == 2) {
                stars = QString(QChar(0x2605)).repeated(2);
            }
            else if (count == 1) {
                stars = QString(QChar(0x2605));
            }
            else {
                stars = QString(QChar(0x2605)).repeated(5); // 如果超出5本书范围 默认为5星
            }


            ui.recommendTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookno())));
            ui.recommendTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookname())));
            ui.recommendTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getauthor())));
            ui.recommendTable->setItem(row, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpublisher())));
            ui.recommendTable->setItem(row, col++, new QTableWidgetItem(stars));

            ui.recommendTable->item(row, 0)->setTextAlignment(Qt::AlignCenter);
            ui.recommendTable->item(row, 1)->setTextAlignment(Qt::AlignCenter);
            ui.recommendTable->item(row, 2)->setTextAlignment(Qt::AlignCenter);
            ui.recommendTable->item(row, 3)->setTextAlignment(Qt::AlignCenter);
            ui.recommendTable->item(row, 4)->setTextAlignment(Qt::AlignCenter);


            for (int col = 0; col < 5; ++col) {

                QTableWidgetItem* pItem = ui.recommendTable->item(row, col);
                pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));

            }


    }
}
void cell_recommend::recommendTableSetting() {
	ui.recommendTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.recommendTable->setColumnCount(5);
	ui.recommendTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("书籍编号")
		<< QString::fromLocal8Bit("书名") << QString::fromLocal8Bit("作者")
		<< QString::fromLocal8Bit("出版公司") << QString::fromLocal8Bit("推荐指数")
	); //借阅日期

	QHeaderView* header = ui.recommendTable->horizontalHeader();
	refreshTable();
	QFont font = ui.recommendTable->horizontalHeader()->font();
	font.setBold(true);
	ui.recommendTable->horizontalHeader()->setFont(font);

    // 设置特定列的宽度
    ui.recommendTable->setColumnWidth(0, 80);  // 第一列宽度设置为100px
    ui.recommendTable->setColumnWidth(1, 680 - 480);  // 第二列宽度设置为80px
    ui.recommendTable->setColumnWidth(3, 150); // 第四列宽度设置为150px
    ui.recommendTable->setColumnWidth(4, 150); // 第五列宽度设置为150px
    ui.recommendTable->setColumnWidth(2, 100);

}
