#pragma once

#include <tuple>
#include "Node.h"
#include "Door.h"
#include "Person.h"

class Node;
class Person;

class Passage {
	Door* door;
	Node* node;

	bool moveIfPossible(int, Person*);
};
