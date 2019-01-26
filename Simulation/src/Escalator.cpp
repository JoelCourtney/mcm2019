#include "Node.h"
#include "Person.h"

void Escalator::update() {
	int peopleLength = people.size();
	for (int i = 0; i < peopleLength;) {
		if (waitTimes.at(i) == waitLimit) {
			if (people.at(i)->move(&directions)) {
				people.erase(people.begin() + i);
				used--;
			} else {
				i++;
			}
		} else {
			waitTimes.at(i)++;
		}
	}
}

bool Escalator::canEnter(int groupID) {
	return used < capacity;
}

void Escalator::enter(Person* person) {
	used++;
	people.push_back(person);
	waitTimes.push_back(0);
}
