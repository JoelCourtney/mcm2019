#include "Graph/Node.h"
#include "Person/Person.h"
#include <iostream>

Exhibit::Exhibit(int ID, int c) : capacity(c), Node(ID) {}

int Exhibit::update() {
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
	return used;
}

bool Exhibit::canEnter(int groupID) {
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
	std::cout << " pref " << directions.normal << std::endl;
}

bool Exhibit::isDangerous() {
	return false;
}
