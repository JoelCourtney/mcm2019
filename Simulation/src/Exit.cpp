#include "Node.h"

void Exit::update() {
	while (people.size() != 0) {
		delete people.back();
		people.pop_back();
	}
}

bool Exit::canEnter(int) {
	return true;
}

void Exit::enter(Person* person) {
	people.push_back(person);
}
