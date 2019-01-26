#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>

Tourist::Tourist(int ID): groupID(ID) {}
Tourist::~Tourist() {std::cout << "bye\n";}

bool Tourist::move(Directions* dir) {
	return dir->normal.moveIfPossible(groupID, this);
}
