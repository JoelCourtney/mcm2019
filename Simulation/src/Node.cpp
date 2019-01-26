#include "Node.h"
#include <iostream>

Node::Node(int ID, float x_, float y_, float z_) : nodeID(ID), x(x_), y(y_), z(z_) {}

void Node::setDirections(Directions d) {
	directions = d;
}

void Node::print() {
	std::cout << "yes heloo i am node" << std::endl;
}
