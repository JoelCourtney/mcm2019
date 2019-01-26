#include "Door.h"

Door::Door(int w) : width(w) {}

bool Door::canMove() {
	return used < width;
}

void Door::move() {
	used++;
}

void Door::reset() {
	used = 0;
}
