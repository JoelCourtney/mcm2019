#pragma once

#include <tuple>
#include "Person/Person.h"
#include "Door.h"

class Node;

class Passage {
	Door* door;
	Node* node;

public:
	Passage();
	Passage(Door*, Node*);

	bool moveIfPossible(int, Person*);
};
