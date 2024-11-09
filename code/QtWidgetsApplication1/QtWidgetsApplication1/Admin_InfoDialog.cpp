#include <QFileDialog>
#include "Admin_InfoDialog.h"
#include "StudentSet.h"
#include "Book.h"
#include <QMessageBox>
#include <string>
#include <QString>



void Admin_InfoDialog::exchange_Set(const string str)
{
    if (str == "current") {
        this->current_BookSet = this->search_BookSet;
        this->current_StuSet = this->search_StuSet;
    }
    else if (str == "original") {
        this->current_BookSet = this->b_set;
        this->current_StuSet = this->s_set;
    }
}

Admin_InfoDialog::Admin_InfoDialog(QWidget* parent)
    : QDialog(parent) //init admin ui
{
    //init variable
    b_set = new BookSet;
    s_set = new StudentSet;
    search_BookSet = new BookSet;
    search_StuSet = new StudentSet;
    b_set->OpenBookList();
    s_set->OpenStuList();
    // The follow code used to change content on UI
    current_BookSet = b_set;
    current_StuSet = s_set;

    ui.setupUi(this);
    set_TabelWghit();
    set_TabelWghit_stu();
    //支持更换页面
    QObject::connect(ui.pb_page1, &QCheckBox::clicked, [this]() {Admin_InfoDialog::set_page(1); });
    QObject::connect(ui.pb_page2, &QCheckBox::clicked, [this]() {Admin_InfoDialog::set_page(2); });
}

Admin_InfoDialog::~Admin_InfoDialog()
{}

void Admin_InfoDialog::set_page(int page_name) { //used for page change
    if (page_name == 1) {
        this->ui.stackedWidget->setCurrentWidget(ui.page);
    }
    else if (page_name == 2) {
        this->ui.stackedWidget->setCurrentWidget(ui.page_2);
    }
}

//图书管理
void Admin_InfoDialog::set_TabelWghit()
// 设置tablewghit的各项参数
{
    //列宽
    this->ui.tableWidget->setColumnWidth(0, 30);
    this->ui.tableWidget->setColumnWidth(1, 80);
    this->ui.tableWidget->setColumnWidth(2, 210);
    this->ui.tableWidget->setColumnWidth(3, 130);
    this->ui.tableWidget->setColumnWidth(4, 100);
    this->ui.tableWidget->setColumnWidth(5, 40);
    this->ui.tableWidget->setColumnWidth(6, 40);
    this->ui.tableWidget->setColumnWidth(7, 100);
    this->ui.tableWidget->setColumnWidth(8, 40);
    refreshTable(current_BookSet);
    refreshTable_stu(current_StuSet);

    //行数
    QObject::connect(ui.pb_add, &QPushButton::clicked, this, &Admin_InfoDialog::add_item_to_TableWghit);
    //链接table表某一行和btn按键
    QObject::connect(ui.pb_delete, &QPushButton::clicked, [this]() {Admin_InfoDialog::delete_book_from_TableWghit(); });
    //链接table表某一行和btn按键
    QObject::connect(ui.pb_sub, &QPushButton::clicked, [this]() {Admin_InfoDialog::cancel_item_from_TableWghit(); });
    //全选
    QObject::connect(ui.Selected_all, &QCheckBox::clicked, [this]() {Admin_InfoDialog::choise_or_unchoise_all_item_from_TableWghit(); });
    //Link search to box
    QObject::connect(ui.search_on, &QCheckBox::toggled, [this]() {Admin_InfoDialog::onSearchAction_book(); });
    QObject::connect(ui.searchLE, &QLineEdit::textChanged, [this]() {Admin_InfoDialog::onSearchAction_book(); });
    //link add_file to button
    QObject::connect(ui.pb_add_book_file, &QCheckBox::clicked, [this]() {Admin_InfoDialog::add_book_from_file(); });
}

void Admin_InfoDialog::add_item_to_TableWghit()
{
    int currentRowCount = this->ui.tableWidget->rowCount();  // 获取当前行数
    this->ui.tableWidget->setRowCount(currentRowCount + 1);  // 增加一行

    btn.push_back(new QPushButton(QString::fromLocal8Bit("确认")));
    mark.push_back(new QCheckBox());
    mark[currentRowCount]->setStyleSheet("QRadioButton { max-width: 20px; }");
    this->ui.tableWidget->setCellWidget(currentRowCount, 8, btn[currentRowCount]);
    this->ui.tableWidget->setCellWidget(currentRowCount, 0, mark[currentRowCount]);
    //链接table表某一行和btn按键
    connect(btn[currentRowCount], &QPushButton::clicked, [this, currentRowCount]() {Admin_InfoDialog::save_or_change_for_TableWghit(currentRowCount); });
    //链接table表某一行和mark浮选,好像不用选
    //connect(mark[currentRowCount], &QCheckBox::clicked, [this, currentRowCount]() {Admin_InfoDialog::chose_mark_for_TableWghit(currentRowCount); });
}

void Admin_InfoDialog::save_or_change_for_TableWghit(int i) //槽函数：当点击确认按钮后保存信息到文件，并修改按钮为修改
{

    int currentRowCount = this->ui.tableWidget->rowCount();  // 获取当前行数
    if (0 > i || i >= currentRowCount)
    {
        return;
    }
    if (btn.at(i)->text() == QString::fromLocal8Bit("更新")) //对于已经保存的文字，允许修改
    {
        Book* book = get_book_from_TableWghit(i);
        if (book == nullptr) {
            return;
        }
        this->b_set->at(find_book_and_return_idx(book)) = *book;
        this->b_set->writeToFile("book.txt");
    }
    else if (btn[i]->text() == QString::fromLocal8Bit("确认"))//对于没有保存的文字，保存
    {
        Book* book = get_book_from_TableWghit(i);
        if (book == nullptr) {
            return;
        }
        btn[i]->setText(QString::fromLocal8Bit("更新"));
        this->b_set->ListInsert_B(*book);
        this->b_set->writeToFile("book.txt");
    }
}

void Admin_InfoDialog::refreshTable(BookSet* set) {
    int i;
    ui.tableWidget->setRowCount(0);
    ui.tableWidget->setRowCount(set->size());

    btn.clear();
    mark.clear();
    BookSet::iterator it;
    //将信息插入表格
    for (it = set->begin(), i = 0; it != set->end(); it++, i++) {
        int col = 1;
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromStdString(it->getbookno())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getbookname())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpublisher())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getauthor())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(it->gettotalnum())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(it->getborrownum())));
        ui.tableWidget->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getpubday().dateFormat())));
        btn.push_back(new QPushButton(QString::fromLocal8Bit("更新")));
        mark.push_back(new QCheckBox());
        connect(btn[i], &QPushButton::clicked, [this, i]() {Admin_InfoDialog::save_or_change_for_TableWghit(i); });
        ui.tableWidget->setCellWidget(i, 8, btn[i]);
        ui.tableWidget->setCellWidget(i, 0, mark[i]);
    }
}

Book* Admin_InfoDialog::get_book_from_TableWghit(int i)
{
    QTableWidgetItem* item_list[10] = { NULL };
    int currentRowCount = this->ui.tableWidget->rowCount();
    if (i >= 0 && i <= currentRowCount) {
        for (int idx = 1; idx <= 8; idx++) {
            item_list[idx] = this->ui.tableWidget->item(i, idx);
        }
        if (item_list[1] == nullptr) {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确书号！"));
            return nullptr;
        }
        if (!isBooknoUnique(i, item_list[1])) {
            return nullptr;
        }
        std::string bookno = getSafeString(item_list[1]);
        if (item_list[2] == nullptr) {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确书名！"));
            return nullptr;
        }
        std::string bookname = getSafeString(item_list[2]);
        if (item_list[4] == nullptr) {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确作者！"));
            return nullptr;
        }
        std::string author = getSafeString(item_list[4]);
        if (item_list[3] == nullptr) {
            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确出版社！"));
            return nullptr;
        }
        std::string publisher = getSafeString(item_list[3]);
        if (item_list[5]->text() == "") {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确书籍总数！"));
            return nullptr;
        }
        int totalnum = item_list[5]->text().toInt();
        if (item_list[6]->text() == "") {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确书籍借阅数量！"));
            return nullptr;
        }
        int borrownum = item_list[6]->text().toInt();
        if (item_list[7] == nullptr || item_list[7]->text() == "" || !isValidDateFormat(item_list[7]->text())) {

            showCustomMessageBox(string("书籍更新状态"), string("失败！请输入正确日期！"));
            return nullptr;
        }
        std::string pubday = getSafeString(item_list[7]);
        Date date(pubday);
        Book* book = new Book;
        book->setbookno(bookno);
        book->setbookname(bookname);
        book->setauthor(author);
        book->setpublisher(publisher);
        book->settotal(totalnum);
        book->setborrow(borrownum);
        book->setday(date);
        return book;
        //this->b_set->ListInsert_B(*book);

    }
}

void Admin_InfoDialog::delete_book_from_TableWghit()
{
    for (int i = 0; i < mark.size(); i++) {
        if (mark[i] != nullptr && mark[i]->isChecked() == true) {
            delete mark[i];
            delete btn[i];
            this->ui.tableWidget->removeRow(i);
            mark.erase(mark.begin() + i);
            btn.erase(btn.begin() + i);
            this->b_set->erase(this->b_set->begin() + find_book_and_return_idx(&(current_BookSet->at(i))));
            i--;
            //这里可以添加删除数据库的函数
        }
    }
    this->b_set->writeToFile("book.txt");
}

int Admin_InfoDialog::find_book_and_return_idx(Book* book) {
    int i = 0;
    for (auto it = b_set->begin(); it != b_set->end(); ++it, i++) {
        if (it->getbookno() == book->getbookno())
            return i; //we assume the bookno has only one;
    }
    return -1;
}

void Admin_InfoDialog::cancel_item_from_TableWghit() {
    //实现取消的功能
    int rowCount = ui.tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++) {
        if (btn[i] != nullptr && btn[i]->text() == QString::fromLocal8Bit("确认")) {
            delete mark[i];
            delete btn[i];
            this->ui.tableWidget->removeRow(i);
            mark.erase(mark.begin() + i);
            btn.erase(btn.begin() + i);
            i--;
            rowCount--;
        }
    }
}

void Admin_InfoDialog::choise_or_unchoise_all_item_from_TableWghit() {
    int rowCount = ui.tableWidget->rowCount();
    bool isSelected = ui.Selected_all->isChecked();
    for (int i = 0; i < rowCount; i++) {
        if (mark[i] != nullptr) {
            mark[i]->setChecked(isSelected);
        }
    }
}

void Admin_InfoDialog::onSearchAction_book() { //used for searching on books

    if (ui.search_on->isChecked())
    {
        this->search_BookSet->clear();
        std::string searchText = ui.searchLE->text().toLocal8Bit().toStdString();
        int i = 0;
        for (auto it = b_set->begin(); it != b_set->end(); ++it, i++) {
            //bool isFound = false;
            bool isFound = it->getauthor().find(searchText) != std::string::npos ||
                it->getbookname().find(searchText) != std::string::npos ||
                it->getbookno().find(searchText) != std::string::npos ||
                std::to_string(it->getborrownum()).find(searchText) != std::string::npos ||  // 使用std::to_string进行转换
                it->getpubday().dateFormat().find(searchText) != std::string::npos ||
                it->getpublisher().find(searchText) != std::string::npos ||
                std::to_string(it->gettotalnum()).find(searchText) != std::string::npos;  // 使用std::to_string进行转换

            if (isFound) {
                this->search_BookSet->push_back(*it);
            }
        }
        exchange_Set("current");
        refreshTable(current_BookSet);
    }//if
    else {
        exchange_Set("original");
        refreshTable(current_BookSet);
    }

}

void Admin_InfoDialog::add_book_from_file() {
    QString filePath = QFileDialog::getOpenFileName(
        this,                   // 父窗口
        tr("select file"),          // 窗口标题
        "",                     // 默认路径
        tr("all files (*.*);; txt file (*.txt)")  // 文件过滤器
    );
    if (!filePath.isEmpty()) {
        // 如果选择了文件，显示文件路径
        QMessageBox::information(this, tr("file path"), tr("your select file path: %1").arg(filePath));
    }
    else {
        // 如果取消了文件选择，提示用户取消了操作
        QMessageBox::information(this, tr("cancel"), tr("you select no file"));
    }
    b_set->Append_book(filePath.toLocal8Bit().toStdString());
    refreshTable(this->current_BookSet);
    this->b_set->writeToFile("book.txt");
}

//学生管理函数

void Admin_InfoDialog::refreshTable_stu(StudentSet* s_set) {
    int i;
    ui.tableWidget_stu->setRowCount(0);
    ui.tableWidget_stu->setRowCount(s_set->size());

    stu_btn.clear();
    stu_mark.clear();

    StudentSet::iterator it;
    //将信息插入表格
    for (it = s_set->begin(), i = 0; it != s_set->end(); it++, i++) {
        int col = 1;
        ui.tableWidget_stu->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getstuno())));
        ui.tableWidget_stu->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getstuname())));
        ui.tableWidget_stu->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getstumajor())));
        ui.tableWidget_stu->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getstuclass())));
        ui.tableWidget_stu->setItem(i, col++, new QTableWidgetItem(QString::fromLocal8Bit(it->getstumobi())));
        stu_btn.push_back(new QPushButton(QString::fromLocal8Bit("更新")));
        stu_mark.push_back(new QCheckBox());
        stu_mark[i]->setStyleSheet("QRadioButton { max-width: 20px; }");
        connect(stu_btn[i], &QPushButton::clicked, [this, i]() {Admin_InfoDialog::save_or_change_for_stu_TableWghit(i); });
        ui.tableWidget_stu->setCellWidget(i, 6, stu_btn[i]);
        ui.tableWidget_stu->setCellWidget(i, 0, stu_mark[i]);
    }
}

void Admin_InfoDialog::set_TabelWghit_stu()
// 设置tablewghit的各项参数
{
    //列宽
    this->ui.tableWidget_stu->setColumnWidth(0, 30);
    this->ui.tableWidget_stu->setColumnWidth(1, 140);
    this->ui.tableWidget_stu->setColumnWidth(2, 80);
    this->ui.tableWidget_stu->setColumnWidth(3, 130);
    this->ui.tableWidget_stu->setColumnWidth(4, 130);
    this->ui.tableWidget_stu->setColumnWidth(5, 130);
    this->ui.tableWidget_stu->setColumnWidth(6, 40);
    //添加行数
    QObject::connect(ui.pb_add_stu, &QPushButton::clicked, [this]() {Admin_InfoDialog::add_item_to_stu_TableWghit(); });
    ////链接table表某一行和btn按键
    QObject::connect(ui.pb_delete_stu, &QPushButton::clicked, [this]() {Admin_InfoDialog::delete_book_from_stu_TableWghit(); });
    ////全选
    QObject::connect(ui.Selected_all_stu, &QCheckBox::clicked, [this]() {Admin_InfoDialog::choise_or_unchoise_all_item_from_stu_TableWghit(); });
    //link search to stu
    QObject::connect(ui.search_on_stu, &QCheckBox::toggled, [this]() {Admin_InfoDialog::onSearchAction_stu(); });
    QObject::connect(ui.searchLE_2, &QLineEdit::textChanged, [this]() {Admin_InfoDialog::onSearchAction_stu(); });
    //link add_file to button
    QObject::connect(ui.pb_add_stu_file, &QCheckBox::clicked, [this]() {Admin_InfoDialog::add_stu_from_file(); });
}

void Admin_InfoDialog::add_item_to_stu_TableWghit() {
    int currentRowCount = this->ui.tableWidget_stu->rowCount();  // 获取当前行数
    this->ui.tableWidget_stu->setRowCount(currentRowCount + 1);  // 增加一行

    stu_btn.push_back(new QPushButton(QString::fromLocal8Bit("确认")));
    stu_mark.push_back(new QCheckBox());
    stu_mark[currentRowCount]->setStyleSheet("QRadioButton { max-width: 20px; }");
    this->ui.tableWidget_stu->setCellWidget(currentRowCount, 6, stu_btn[currentRowCount]);
    this->ui.tableWidget_stu->setCellWidget(currentRowCount, 0, stu_mark[currentRowCount]);
    //链接table表某一行和btn按键
    connect(stu_btn[currentRowCount], &QPushButton::clicked, [this, currentRowCount]() {Admin_InfoDialog::save_or_change_for_stu_TableWghit(currentRowCount); });
    //链接table表某一行和mark浮选,好像不用选
    //connect(mark[currentRowCount], &QCheckBox::clicked, [this, currentRowCount]() {Admin_InfoDialog::chose_mark_for_TableWghit(currentRowCount); });
}

void Admin_InfoDialog::save_or_change_for_stu_TableWghit(int i) //槽函数：当点击确认按钮后保存信息到文件，并修改按钮为修改
{

    int currentRowCount = this->ui.tableWidget_stu->rowCount();  // 获取当前行数
    if (0 > i || i >= currentRowCount)
    {
        return;
    }
    if (stu_btn.at(i)->text() == QString::fromLocal8Bit("更新")) //对于已经保存的文字，允许修改
    {
        Student* stu = get_student_from_stu_TableWghit(i);
        if (stu == nullptr) {
            return;
        }
        s_set->at(find_stu_and_return_idx(stu)) = stu;
        s_set->writeToFile("student1.txt");
    }
    else if (stu_btn[i]->text() == QString::fromLocal8Bit("确认"))//对于没有保存的文字，保存
    {
        Student* stu = get_student_from_stu_TableWghit(i);
        if (stu == nullptr) {
            return;
        }
        stu_btn[i]->setText(QString::fromLocal8Bit("更新"));
        s_set->ListInsert_S(*stu);
        s_set->writeToFile("student1.txt");
    }
}

void Admin_InfoDialog::delete_book_from_stu_TableWghit() {
    for (int i = 0; i < stu_mark.size(); i++) {
        if (stu_mark[i] != nullptr && stu_mark[i]->isChecked() == true) {
            delete stu_mark[i];
            delete stu_btn[i];
            this->ui.tableWidget_stu->removeRow(i);
            stu_mark.erase(stu_mark.begin() + i);
            stu_btn.erase(stu_btn.begin() + i);
            s_set->erase(s_set->begin() + find_stu_and_return_idx(&(current_StuSet->at(i))));
            s_set->writeToFile("student1.txt");
            i--;

        }
    }
}

void Admin_InfoDialog::choise_or_unchoise_all_item_from_stu_TableWghit() {
    int rowCount = ui.tableWidget_stu->rowCount();
    bool isSelected = ui.Selected_all_stu->isChecked();
    for (int i = 0; i < rowCount; i++) {
        if (stu_mark[i] != nullptr) {
            stu_mark[i]->setChecked(isSelected);
        }
    }
}

Student* Admin_InfoDialog::get_student_from_stu_TableWghit(int i)
{
    QTableWidgetItem* item_list[6] = { NULL };
    int currentRowCount = this->ui.tableWidget_stu->rowCount();
    if (i >= 0 && i <= currentRowCount) {
        for (int idx = 1; idx <= 5; idx++) {
            item_list[idx] = this->ui.tableWidget_stu->item(i, idx);
        }
        if (item_list[1] == nullptr) {

            showCustomMessageBox(string("读者更新状态"), string("失败！请输入正确学号！"));
            return nullptr;
        }
        if (!isStunoUnique(i, item_list[1])) {
            return nullptr;
        }
        std::string studentno = getSafeString(item_list[1]);
        if (item_list[2] == nullptr) {

            showCustomMessageBox(string("读者更新状态"), string("失败！请输入正确读者姓名！"));
            return nullptr;
        }
        std::string studentname = getSafeString(item_list[2]);
        if (item_list[3] == nullptr) {

            showCustomMessageBox(string("读者更新状态"), string("失败！请输入正确读者专业！"));
            return nullptr;
        }
        std::string studentmajor = getSafeString(item_list[3]);
        if (item_list[4] == nullptr) {

            showCustomMessageBox(string("读者更新状态"), string("失败！请输入正确读者班级！"));
            return nullptr;
        }
        std::string studentclass = getSafeString(item_list[4]);
        if (item_list[5] == nullptr || !requireInt(item_list[5]->text()) || item_list[5]->text().length() != 11) {

            showCustomMessageBox(string("读者更新状态"), string("失败！请输入正确读者电话！"));
            return nullptr;
        }
        std::string studentmobile = getSafeString(item_list[5]);

        Student* stu = new Student;
        stu->setstuno(studentno);
        stu->setstuname(studentname);
        stu->setstumajor(studentmajor);
        stu->setstuclass(studentclass);
        stu->setstumobi(studentmobile);
        return stu;

    }
}

int Admin_InfoDialog::find_stu_and_return_idx(Student* stu) {
    int i = 0;
    for (auto it = s_set->begin(); it != s_set->end(); ++it, i++) {
        if (it->getstuno() == stu->getstuno())
            return i; //we assume the stuno has only one;
    }
    return -1;
}

void Admin_InfoDialog::onSearchAction_stu() { //used for searching on books

    if (ui.search_on_stu->isChecked())
    {
        this->search_StuSet->clear();
        std::string searchText = ui.searchLE_2->text().toLocal8Bit().toStdString();
        int i = 0;
        for (auto it = s_set->begin(); it != s_set->end(); ++it, i++) {
            //bool isFound = false;
            bool isFound = it->getstuno().find(searchText) != std::string::npos ||
                it->getstuname().find(searchText) != std::string::npos ||
                it->getstumajor().find(searchText) != std::string::npos ||
                it->getstuclass().find(searchText) != std::string::npos ||
                it->getstumobi().find(searchText) != std::string::npos;  // 使用std::to_string进行转换

            if (isFound) {
                this->search_StuSet->push_back(*it);
            }
        }
        exchange_Set("current");
        refreshTable_stu(current_StuSet);
    }//if
    else {
        exchange_Set("original");
        refreshTable_stu(current_StuSet);
    }

}

void Admin_InfoDialog::add_stu_from_file() {
    QString filePath = QFileDialog::getOpenFileName(
        this,                   // 父窗口
        tr("select file"),          // 窗口标题
        "",                     // 默认路径
        tr("all files (*.*);; txt file (*.txt)")  // 文件过滤器
    );
    if (!filePath.isEmpty()) {
        // 如果选择了文件，显示文件路径
        QMessageBox::information(this, tr("file path"), tr("your select file path: %1").arg(filePath));
    }
    else {
        // 如果取消了文件选择，提示用户取消了操作
        QMessageBox::information(this, tr("cancel"), tr("you select no file"));
    }
    s_set->Append_stu(filePath.toLocal8Bit().toStdString());
    refreshTable_stu(this->current_StuSet);
    s_set->writeToFile("student1.txt");
}

//安全性管理
bool Admin_InfoDialog::requireInt(const QString& str)
{
    return std::all_of(str.begin(), str.end(), [](QChar ch) {
        return ch.isDigit();
        });
}
bool Admin_InfoDialog::isValidDateFormat(const QString& Qstr) {
    // 将 QString 转换为 std::string
    std::string str = Qstr.toLocal8Bit().toStdString();
    int year_pos = str.find("年");
    int month_pos = str.find("月");
    int day_pos = str.find("日");

    if (year_pos + 2 >= month_pos || month_pos + 2 >= day_pos) {
        return false;
    }
    //年
    if (!isNumber(str.substr(0, year_pos)) || str.substr(0, year_pos).size() != 4) {
        return false;
    }
    if (!isNumber(str.substr(year_pos + 2, month_pos - (year_pos + 2))) || std::stoi(str.substr(year_pos + 2, month_pos - (year_pos + 2))) > 12 || std::stoi(str.substr(year_pos + 2, month_pos - (year_pos + 2))) <= 0) {
        return false;
    }
    if (!isNumber(str.substr(month_pos + 2, day_pos - (month_pos + 2))) || std::stoi(str.substr(month_pos + 2, day_pos - (month_pos + 2))) > 31 || std::stoi(str.substr(month_pos + 2, day_pos - (month_pos + 2))) <= 0) {
        return false;
    }
    return true;
}
string Admin_InfoDialog::getSafeString(const QTableWidgetItem* item) {
    if (item != nullptr) {
        QString str = item->text();
        // 检查字符串是否为空
        if (!str.isEmpty()) {
            return str.toLocal8Bit().toStdString();
        }
        else {
            // 处理空输入的情况
            return "";
        }
    }
    else {
        // 处理 item_list[1] 为 nullptr 的情况
        return "";  // 或者给 studentno 赋予一个默认值
    }
}
void Admin_InfoDialog::showCustomMessageBox(const std::string& title, const std::string& message) {
    //QMessageBox msgBox;
    //msgBox.setWindowTitle(title);  // 设置窗口标题
    //msgBox.setText(message);       // 设置窗口提示内容
    //msgBox.setIcon(QMessageBox::Information);  // 设置提示框的图标
    //msgBox.exec();  // 显示窗口

    QMessageBox msgBox1;
    QString str = QString::fromLocal8Bit(message);
    msgBox1.setIcon(QMessageBox::Warning);
    msgBox1.setWindowTitle(QString::fromLocal8Bit(title));
    msgBox1.setText(str);
    msgBox1.resize(900, 900); // 设置固定大小

    msgBox1.exec();
}
bool Admin_InfoDialog::isNumber(string str) {
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;

}
bool Admin_InfoDialog::isBooknoUnique(int i, QTableWidgetItem* item) {
    Book* ptr = NULL;
    string str = getSafeString(item);
    if (i < b_set->size()) {
        ptr = &b_set->at(i);
    }
    for (auto it = b_set->begin(); it != b_set->end(); ++it) {
        // Check if the iterator points to the current item
        if (&(*it) != ptr && it->getbookno() == str) {
            showCustomMessageBox(string("错误"),string("存在相同书号，请重新输入！"));
            return false;
        }
    }
    return true;
}

bool Admin_InfoDialog::isStunoUnique(int i, QTableWidgetItem* item) {

    Student* ptr = NULL;
    string str = getSafeString(item);
    if (i < s_set->size()) {
        ptr = &s_set->at(i);
    }
    for (auto it = s_set->begin(); it != s_set->end(); ++it) {
        // Check if the iterator points to the current item
        if (&(*it) != ptr && it->getstuno() == str) {

            showCustomMessageBox(string("读者更新状态"), string("失败！存在相同学号！"));

            return false;
        }
    }
    return true;
}


