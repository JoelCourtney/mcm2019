#include "Node.h"
#include <iostream>

Exit::Exit(int ID, float x_, float y_, float z_) : Node(ID,x_,y_,z_) {}


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
