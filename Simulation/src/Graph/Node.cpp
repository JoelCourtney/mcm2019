#include "Graph/Node.h"
#include <iostream>

Node::Node(int ID) : nodeID(ID) {}

void Node::addPassage(Passage p) {
	directions.passages.push_back(p);
}

void Node::changePreference(int t) {
	if (t == 0) directions.normal = directions.passages.size()-1;
	else if (t == 1) directions.disabled = directions.passages.size()-1;
	else if (t == 2) directions.police = directions.passages.size()-1;
}

void Node::print() {
	std::cout << "yes heloo i am node" << std::endl;
}

int Node::getID() {
	return nodeID;
}
