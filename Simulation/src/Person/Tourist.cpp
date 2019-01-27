#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>
#include <stdlib.h>

Tourist::Tourist(int ID): groupID(ID) {}
Tourist::~Tourist() {}

bool Tourist::move(Directions* dir) {
	if (dir->normal >= 0 && dir->normal < dir->passages.size()) {
		return dir->passages.at(dir->normal).moveIfPossible(groupID, this);
	} else {
		return dir->passages.at(std::rand() % dir->passages.size()).moveIfPossible(groupID, this);
	}
}
