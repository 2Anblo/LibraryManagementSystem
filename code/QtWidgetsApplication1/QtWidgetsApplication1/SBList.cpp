# include "SBList.h"

Status SBList::begin_borrow() {
	//������Ϣ��ʼ�� 
	studentnum = 0;     //����������Ϊ0 
	borrownum = 0;      //���ȥ���鼮������Ϊ0 
	return OK;
}

Status SBList::OpenBorrowList()     //�����ļ��еĽ�����Ϣ 
{
	ifstream INFILE("borrow.txt");
	BorrowInfo b;
	string sno, bno;
	if (!INFILE)
	{
		cout << "�ļ���ȡʧ��,�������ݸ�ʽ!\n";
		return ERROR;
	}  // ����ʧ�� 
	INFILE >> studentnum;    //�ж���ѧ����������    
	studentnum = 0;     //����������Ϊ0 
	borrownum = 0;              //���ȥ����������0 
	while (!INFILE.eof())
	{
		StudentNode s;
		INFILE >> s;
		this->pushelem(s);
		borrownum += s.getborrownum();
	}
	INFILE.close();
	cout << "�ļ������ѳɹ�!\n";
	return OK;
}

Status SBList::WriteToFile()
{
	ofstream OUTFILE("borrow.txt");
	if (!OUTFILE)
	{
		return ERROR;
	}

	// д��ѧ��������Ϣ������

	OUTFILE << studentnum ;

	// ����SBList��StudentNode����Ϣ��ÿ��д���ļ�
		StudentNodeSet s = this->getSBList(); // ������һ��getelem�������Ի�ȡָ��������ѧ���ڵ�
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