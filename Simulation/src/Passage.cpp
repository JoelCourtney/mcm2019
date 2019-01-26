#include "Passage.h"
#include "Node.h"

Passage::Passage() {}

Passage::Passage(Door* d, Node* n) : door(d), node(n) {}

bool Passage::moveIfPossible(int groupID, Person* person) {
	if (!door->canMove()) return false;
	if (!node->canEnter(groupID)) return false;
	door->move();
	node->enter(person);
	return true;
}
