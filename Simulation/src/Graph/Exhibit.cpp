#include "Graph/Node.h"
#include "Person/Person.h"
#include <iostream>

Exhibit::Exhibit(int ID, float x_, float y_, float z_, int c) : capacity(c), Node(ID,x_,y_,z_) {}

void Exhibit::update() {
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
}

bool Exhibit::canEnter(int groupID) {
	return used < capacity;
}

void Exhibit::enter(Person* person) {
	used++;
	people.push_back(person);
}

void Exhibit::print() {
	//if (people.size() > 0)
		std::cout << "ID: " << nodeID << ". " << used << " people are currently here." << std::endl;
}
