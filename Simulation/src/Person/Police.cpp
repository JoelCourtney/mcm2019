#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>
#include <stdlib.h>


bool Police::move(Directions* dir) {
	if (!(dir->passages.at(dir->police).moveIfPossible(0, this))) {
		if (rand()%70 == 0)
			return dir->passages.at(std::rand() % dir->passages.size()).moveIfPossible(0, this);
		else return false;
	}
	return true;
}

int Police::getType() {
	return PersonType::Police;
}
