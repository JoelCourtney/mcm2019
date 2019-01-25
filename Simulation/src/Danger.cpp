#include "Node.h"

void Danger::update() {
	Exhibit::update();
}

bool Danger::canEnter(int groupID) {
	return used < capacity;
}
