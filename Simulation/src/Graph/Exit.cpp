#include "Graph/Node.h"
#include <iostream>

Exit::Exit(int ID) : Node(ID) {}


void Exit::update() {
	for (int i = 0; i < people.size(); i++) {
		delete people.at(i);
		used++;
	}
	people.clear();
}

bool Exit::canEnter(int) {
	return true;
}

void Exit::enter(Person* person) {
	people.push_back(person);
}

void Exit::print() {
	std::cout << "ID: " << nodeID << ". " << used << " people have exited here." << std::endl;
}
