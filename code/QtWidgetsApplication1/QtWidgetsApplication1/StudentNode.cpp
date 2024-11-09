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
		cout << iter->getbookno() << "          " << iter->getborrowday().getyear() << "��" << iter->getborrowday().getmonth() << "��" << iter->getborrowday().getday() << "��" << endl;
	}
}

void StudentNode::printsinglebookinfo(string bn)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (bn == iter->getbookno())
			cout << "ѧ��" << studentno << "��" << iter->getborrowday().getyear() << "��" << iter->getborrowday().getmonth() << "��" << iter->getborrowday().getday() << "�� ���߱��Ϊ��" << iter->getbookno() << "���鼮��" << endl;
	}
}

void StudentNode::outdate(Date now, StudentSet stu)
{
	vector<BorrowInfo>::iterator iter;
	for (iter = bilist.begin(); iter != bilist.end(); iter++)
	{
		if (iter->getborrowday().subday(now))
		{
			cout << "ѧ��" << studentno << "��" << iter->getborrowday().getyear() << "��" << iter->getborrowday().getmonth() << "��" << iter->getborrowday().getday() << "�� ���߱��Ϊ��" << iter->getbookno() << "���鼮��   �Ѿ�����30�죡����" << endl;
			vector<Student>::iterator iterstu;
			for (iterstu = stu.begin(); iterstu != stu.end(); iterstu++)
				if (studentno == iterstu->getstuno())
				{
					//cout <<"���ֻ�����" << iterstu->getstumobi() << "ͬѧ������\n";
					break;
				}
			if (iterstu == stu.end())
			{
				cout << "û���ҵ���ͬѧ!\n";
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
	bool isFirst = true; // �����ж��Ƿ��ǵ�һ����¼

	for (iter = sn.bilist.begin(); iter != sn.bilist.end(); iter++)
	{
		os << endl << sn.studentno << " " << *iter;
	}
	return os;
}
