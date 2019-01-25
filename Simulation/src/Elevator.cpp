#include "Node.h"

void Elevator::update() {
	if (moving) {
		if (waitTime == waitLimit) {
			int peopleLength = people.size();
			for (int i = 0; i < peopleLength;) {
				if (people.at(i)->move(&directions)) {
					people.erase(people.begin() + i);
					used--;
				} else {
					i++;
				}
			}
			if (used == 0) {
				waitTime = 0;
				moving = false;
			}
		} else {
			waitTime++;
		}
	} else {
		if (used > 0) {
			if (used < capacity) {
				if (waitTime == waitLimit) {
					waitTime = 0;
					moving = true;
				} else {
					waitTime++;
				}
			} else {
				waitTime = 0;
				moving = true;
			}
		}
	}
}

bool Elevator::canEnter(int groupID) {
	return !moving && (used < capacity);
}

void Elevator::enter(Person* person) {
	used++;
	people.insert(people.begin(),person);
}
