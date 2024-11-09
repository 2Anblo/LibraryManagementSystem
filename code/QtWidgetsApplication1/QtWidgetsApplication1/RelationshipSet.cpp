#include "RelationshipSet.h"


//RelationshipSet();
//virtual ~RelationshipSet();
Status RelationshipSet::DeQueue(Relationship& e)   //出
{
	if (this->size() == 0)
		return ERROR; //空
	vector<Relationship>::iterator iter = this->begin();
	e = *iter;
	this->erase(iter);
	return OK;
}

Status RelationshipSet::EnQueue(Relationship e)    //进
{ //在队尾插入元素e 
	this->push_back(e);
	return OK;
}

Status RelationshipSet::QueueEmpty()
{//队列为空返回1，否则返回0 
	if (this->size() == 0) return OK;
	return ERROR;
}
