#include "Graph/Node.h"
#include <iostream>

Room::Room(int ID, int cap): Exhibit(ID,cap) {}

int Room::getNumberOfPeople() {
	return used;
}

void Room::print() {
	std::cout << "ID: " << nodeID << " | " << used;
	for (int i = 0; i < directions.passages.size(); i++) {
		std::cout << "->" << directions.passages.at(i).node->getID();
	}
	std::cout << " pref " << directions.normal << std::endl;
}

bool Room::isDangerous() {
	return false;
}
