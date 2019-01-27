#pragma once

#include <tuple>
#include "Person/Person.h"
#include "Door.h"

class Node;

struct Passage {
	Door* door;
	Node* node;

public:
	Passage();
	Passage(Door*, Node*);

	bool moveIfPossible(int, Person*);
};
