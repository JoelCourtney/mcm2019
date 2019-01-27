#include "Graph/Passage.h"
#include "Graph/Node.h"
#include <iostream>

Passage::Passage() {}

Passage::Passage(Door* d, Node* n) : door(d), node(n) {}

bool Passage::moveIfPossible(int groupID, Person* person) {
	if (!door->canMove(groupID)) return false;
	if (!node->canEnter(groupID)) return false;
	door->move(groupID);
	node->enter(person);
	return true;
}
