# include "Relationship.h"
#include "PreDefination.h"

class RelationshipSet :public vector < Relationship >
{
public:
	//RelationshipSet();
	//virtual ~RelationshipSet();
	Status DeQueue(Relationship& e);   //³ö

	Status EnQueue(Relationship e);    //½ø

	Status QueueEmpty();
};