# include "Relationship.h"
#include "PreDefination.h"

class RelationshipSet :public vector < Relationship >
{
public:
	//RelationshipSet();
	//virtual ~RelationshipSet();
	Status DeQueue(Relationship& e);   //��

	Status EnQueue(Relationship e);    //��

	Status QueueEmpty();
};