#include "Graph/Door.h"
#include <stdlib.h>

Door::Door(int w) : width(w) {}

bool Door::canMove(int groupID) {
	if (!activeGroup || activeGroup == groupID)
		return used < width;
	else {
		if (std::rand() % 10 < bias) {
			bias += 2;
			return true;
		} else {
			bias++;
			return false;
		}
	}
}

void Door::move(int groupID) {
	if (groupID != 0) {
		activeGroup = groupID;
		bias = 0;
	}
	used++;
}

void Door::reset() {
	used = 0;
	activeGroup = 0;
	bias = 11;
}
