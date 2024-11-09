# include "StudentNode.h"

void StudentNode::setstudentno(string no)
{
	studentno = no;
}

void StudentNode::setborrownum(int b)
{
	borrownum = b;
}

void StudentNode::pushbook(BorrowInfo b)
{
	bilist.push_back(b);
	borrownum++;
}

string StudentNode::getstudentno()
{
	return studentno;
}

int StudentNode::getborrownum()
{
	return borrownum;
}

int StudentNode::BookWhetherIn(string bn)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (iter->getbookno() == bn)
			return 1;
	}
	return 0;
}

void StudentNode::returnbook(string bn)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (iter->getbookno() == bn)
		{
			bilist.erase(iter);
			borrownum--;
			break;
		}
	}
}

void StudentNode::printallbookinfo()
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		cout << iter->getbookno() << "          " << iter->getborrowday().getyear() << "年" << iter->getborrowday().getmonth() << "月" << iter->getborrowday().getday() << "日" << endl;
	}
}

void StudentNode::printsinglebookinfo(string bn)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (bn == iter->getbookno())
			cout << "学生" << studentno << "于" << iter->getborrowday().getyear() << "年" << iter->getborrowday().getmonth() << "月" << iter->getborrowday().getday() << "日 借走编号为：" << iter->getbookno() << "的书籍！" << endl;
	}
}

void StudentNode::outdate(Date now, StudentSet stu)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (iter->getborrowday().subday(now))
		{
			cout << "学生" << studentno << "于" << iter->getborrowday().getyear() << "年" << iter->getborrowday().getmonth() << "月" << iter->getborrowday().getday() << "日 借走编号为：" << iter->getbookno() << "的书籍！   已经超过30天！！！" << endl;
			vector<Student>::iterator iterstu;
			for (iterstu = stu.begin(); iterstu != stu.end(); iterstu++)
				if (studentno == iterstu->getstuno())
				{
					//cout <<"给手机号是" << iterstu->getstumobi() << "同学发短信\n";
					break;
				}
			if (iterstu == stu.end())
			{
				cout << "没有找到此同学!\n";
			}
		}
	}
}

BorrowInfoSet& StudentNode::getblist() {
	return bilist;
}


std::istream& operator>>(std::istream& is, StudentNode& sn)
{
	is >> sn.studentno;
	int num;
	is >> num;
	for (; num > 0; num--)
	{
		string snotemp;
		is >> snotemp;
		BorrowInfo btemp;
		is >> btemp;
		sn.pushbook(btemp);
	}
	return is;
}
std::ostream& operator<<(std::ostream& os, StudentNode& sn)
{
	os << endl << sn.studentno << " " << sn.borrownum ;
	vector<BorrowInfo>::iterator iter;
	bool isFirst = true; // 用于判断是否是第一条记录

	for (iter = sn.bilist.begin(); iter != sn.bilist.end(); iter++)
	{
		os << endl << sn.studentno << " " << *iter;
	}
	return os;
}
