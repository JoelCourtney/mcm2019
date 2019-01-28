#include "Graph/Node.h"
#include "Person/Person.h"
#include <iostream>

Exhibit::Exhibit(int ID, int c) : capacity(c), Node(ID) {}

int Exhibit::update() {
	int peopleLength = people.size();
	bool moved = peopleLength == 0;
	for (int i = 0; i < peopleLength;) {
		if (people.at(i)->move(&directions)) {
			moved = true;
			people.erase(people.begin() + i);
			used--;
			peopleLength--;
		} else {
			i++;
		}
	}
	//if (!moved)
		//std::cout << "ID: " << nodeID << " no one moved\n";
	int count = used;
	for (int i = 0; i < exhibits.size(); i++) {
		count += exhibits.at(i)->getNumberOfPeople();
	}
	return used;
}

bool Exhibit::canEnter(int groupID) {
	//if (used >= capacity) std::cout << "ID: " << nodeID << " is full: " << used << std::endl;
	return used < capacity;
}

void Exhibit::enter(Person* person) {
	used++;
	people.push_back(person);
}

void Exhibit::addRoom(Exhibit* e) {
	exhibits.push_back(e);
}

void Exhibit::print() {
	//if (people.size() > 0)
	std::cout << "ID: " << nodeID << " | " << used;
	for (int i = 0; i < directions.passages.size(); i++) {
		std::cout << "->" << directions.passages.at(i).node->getID();
	}
	std::cout << " pref " << directions.disabled << std::endl;
}

bool Exhibit::isDangerous() {
	return false;
}
