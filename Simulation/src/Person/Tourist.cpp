#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>
#include <stdlib.h>

Tourist::Tourist(int ID): groupID(ID) {}
Tourist::~Tourist() {}

bool Tourist::move(Directions* dir) {
	if (!(dir->passages.at(dir->normal).moveIfPossible(groupID, this))) {
		if (rand()%70 == 0)
			return dir->passages.at(std::rand() % dir->passages.size()).moveIfPossible(groupID, this);
		else return false;
	}
	return true;
}

int Tourist::getType() {
	return PersonType::Normal;
}
