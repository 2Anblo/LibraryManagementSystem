#include "RelationshipSet.h"


//RelationshipSet();
//virtual ~RelationshipSet();
Status RelationshipSet::DeQueue(Relationship& e)   //��
{
	if (this->size() == 0)
		return ERROR; //��
	vector<Relationship>::iterator iter = this->begin();
	e = *iter;
	this->erase(iter);
	return OK;
}

Status RelationshipSet::EnQueue(Relationship e)    //��
{ //�ڶ�β����Ԫ��e 
	this->push_back(e);
	return OK;
}

Status RelationshipSet::QueueEmpty()
{//����Ϊ�շ���1�����򷵻�0 
	if (this->size() == 0) return OK;
	return ERROR;
}
