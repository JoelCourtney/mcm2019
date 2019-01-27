#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>

Tourist::Tourist(int ID): groupID(ID) {}
Tourist::~Tourist() {}

bool Tourist::move(Directions* dir) {
	return dir->passages.at(dir->normal).moveIfPossible(groupID, this);
}
