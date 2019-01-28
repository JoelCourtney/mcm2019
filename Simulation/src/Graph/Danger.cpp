#include "Graph/Node.h"
#include <iostream>

Danger::Danger(int ID, int cap) : Exhibit(ID,cap) {}

int Danger::update() {
	int peopleLength = people.size();
	bool moved = peopleLength == 0;
	for (int i = 0; i < peopleLength;) {
		if (people.at(i)->getType() == PersonType::Police) {
			std::cout << "hi\n";
			delete people.at(i);
			people.erase(people.begin() + i);
			peopleLength--;
			used--;
			exited++;
		} else if (people.at(i)->move(&directions)) {
			people.erase(people.begin() + i);
			used--;
			peopleLength--;
			moved = true;
		} else {
			i++;
		}
	}
	int count = used;
	for (int i = 0; i < exhibits.size(); i++) {
		count += exhibits.at(i)->getNumberOfPeople();
	}
	return used;
	//for (int i = 0; i < people.size(); i++) {
		//delete people.at(i);
		//used++;
	//}
	//people.clear();
	//return used;
}

int Danger::getNumberOfPeople() {
	return used;
}

bool Danger::canEnter(int) {
	return true;
}

void Danger::print() {
	std::cout << "DANGER AT " << nodeID << " | " << used << std::endl;
}

bool Danger::isDangerous() {
	return true;
}

int Danger::getExited() {
	return exited;
}
