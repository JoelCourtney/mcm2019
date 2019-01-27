#include "Graph/Node.h"
#include "Person/Person.h"
#include <iostream>

Escalator::Escalator(int ID, int cap, int lim): capacity(cap), waitLimit(lim), Node(ID) {}

int Escalator::update() {
	int peopleLength = people.size();
	for (int i = 0; i < peopleLength;) {
		if (waitTimes.at(i) == waitLimit) {
			if (people.at(i)->move(&directions)) {
				people.erase(people.begin() + i);
				waitTimes.erase(waitTimes.begin() + i);
				used--;
				peopleLength--;
			} else {
				i++;
			}
		} else {
			waitTimes.at(i)++;
			i++;
		}
	}
	return used;
}

bool Escalator::canEnter(int groupID) {
	return used < capacity;
}

void Escalator::enter(Person* person) {
	used++;
	people.push_back(person);
	waitTimes.push_back(0);
}

void Escalator::print() {
	std::cout << "Escalator " << nodeID << " moving " << used << " people." << std::endl;
}
