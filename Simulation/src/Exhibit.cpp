#include "Node.h"

void Exhibit::update() {
	int peopleLength = people.size();
	for (int i = 0; i < peopleLength;) {
		if (people.at(i)->move(&directions)) {
			people.erase(people.begin() + i);
			used--;
		} else {
			i++;
		}
	}
}

bool Exhibit::canEnter(int groupID) {
	return used < capacity;
}

void Exhibit::enter(Person* person) {
	used++;
	people.push_back(person);
}
