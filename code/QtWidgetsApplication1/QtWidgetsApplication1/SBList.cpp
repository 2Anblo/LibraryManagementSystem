# include "SBList.h"

Status SBList::begin_borrow() {
	//借阅信息初始化 
	studentnum = 0;     //借阅人数设为0 
	borrownum = 0;      //借出去的书籍数量设为0 
	return OK;
}

Status SBList::OpenBorrowList()     //读入文件中的借阅信息 
{
	ifstream INFILE("borrow.txt");
	BorrowInfo b;
	string sno, bno;
	if (!INFILE)
	{
		cout << "文件读取失败,请检查数据格式!\n";
		return ERROR;
	}  // 读入失败 
	INFILE >> studentnum;    //有多少学生借走了书    
	studentnum = 0;     //借阅人数设为0 
	borrownum = 0;              //借出去的书总数归0 
	while (!INFILE.eof())
	{
		StudentNode s;
		INFILE >> s;
		this->pushelem(s);
		borrownum += s.getborrownum();
	}
	INFILE.close();
	cout << "文件载入已成功!\n";
	return OK;
}

Status SBList::WriteToFile()
{
	ofstream OUTFILE("borrow.txt");
	if (!OUTFILE)
	{
		return ERROR;
	}

	// 写入学生借阅信息的数量

	OUTFILE << studentnum ;

	// 遍历SBList，StudentNode的信息将每个写入文件
		StudentNodeSet s = this->getSBList(); // 假设有一个getelem方法可以获取指定索引的学生节点
		for (auto i : s)
		{
			OUTFILE << i;
		}

	OUTFILE.close();
	return OK;
}

int SBList::StuWhetherIn(string no)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (no == iter->getstudentno())
			return 1;
	}
	return 0;
}

void SBList::pushelem(StudentNode sn)
{
	sblist.push_back(sn);
	studentnum++;
}

void SBList::setstudentnum(int s)
{
	studentnum = s;
}

void SBList::setborrownum(int b)
{
	borrownum = b;
}

int SBList::getstudentnum()
{
	return studentnum;
}

int SBList::getborrownum()
{
	return borrownum;
}

int SBList::getpersonalnum(string no)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (no == iter->getstudentno())
			break;
	}
	return iter->getborrownum();
}

int SBList::BookWhetherIn(string sn, string bn)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (sn == iter->getstudentno())
			break;
	}
	return iter->BookWhetherIn(bn);
}


bool SBList::bookLimit(string sn) {
	vector<StudentNode>::iterator iter;


	
		for (iter = sblist.begin(); iter != sblist.end(); iter++)
		{
			if (sn == iter->getstudentno())
				break;
		}
	
	if (iter == sblist.end()) {
			return true;
	}
	else
	{
		return iter->getborrownum() < 5;
	}
	
}

void SBList::addanewrelation(string sn, BorrowInfo bi)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (sn == iter->getstudentno())
			break;
	}
	
	iter->pushbook(bi);
	borrownum++;
}

void SBList::returnbook(string sn, string bn)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (sn == iter->getstudentno())
			break;
	}
	iter->returnbook(bn);
	borrownum--;
	if (iter->getborrownum() == 0)
	{
		sblist.erase(iter);
		studentnum--;
	}
}

void SBList::printbookinfo(string sn)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		if (sn == iter->getstudentno())
			iter->printallbookinfo();
	}
}

void SBList::printsinglebookinfo(string bn)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		iter->printsinglebookinfo(bn);
	}
}

void SBList::outdate(Date now, StudentSet stu)
{
	vector<StudentNode>::iterator iter;
	for (iter = sblist.begin(); iter != sblist.end(); iter++)
	{
		iter->outdate(now, stu);
	}
}
StudentNodeSet SBList::getSBList() {
	return sblist;
}