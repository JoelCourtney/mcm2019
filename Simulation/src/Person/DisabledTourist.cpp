#include "Person/Person.h"
#include "Graph/Directions.h"
#include <iostream>

class Node;

DisabledTourist::DisabledTourist(int ID): Tourist(ID) {}

bool DisabledTourist::move(Directions* dir) {
	if (dir->disabled < 0 || dir->disabled >= dir->passages.size()) {
		std::cout << "Would like to go to " << dir->disabled << " but have to go to " << (dir->normal) << std::endl;
		return dir->passages.at(dir->normal).moveIfPossible(groupID, static_cast<Person*>(this));
	}
	//for (int i = 0; i < previous.size(); i++) {
		//if (dir->passages.at(dir->disabled).node == previous.at(i)) {
			//std::cout << "Been here before: " << dir->passages.at(dir->disabled).node << std::endl;
		//}
	//}
	//previous.push_back(dir->passages.at(dir->disabled).node);
	bool res = dir->passages.at(dir->disabled).moveIfPossible(groupID, static_cast<Person*>(this));
	//if (!res) std::cout << "move failed\n";
	return res;
}

int DisabledTourist::getType() {
	return PersonType::Disabled;
}
