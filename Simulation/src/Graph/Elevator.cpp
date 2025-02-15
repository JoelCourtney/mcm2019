#include "Graph/Node.h"
#include "Person/Person.h"
#include <iostream>

Elevator::Elevator(int ID, int cap, int lim): capacity(cap), waitLimit(lim), Node(ID) {waitTime = 0;}

int Elevator::update() {
	if (moving) {
		if (waitTime == waitLimit) {
			int peopleLength = people.size();
			for (int i = 0; i < peopleLength;) {
				if (people.at(i)->move(&directions)) {
					people.erase(people.begin() + i);
					used--;
					peopleLength--;
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
	return used;
}

bool Elevator::canEnter(int groupID) {
	return !moving && (used < capacity);
}

void Elevator::enter(Person* person) {
	used++;
	people.insert(people.begin(),person);
}

void Elevator::print() {
	std::cout << "Elevator " << nodeID << " waiting " << waitTime << " with " << used << " people for " << directions.passages.at(directions.disabled).node->getID() << std::endl;
}
