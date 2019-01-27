#include "BasicGraph/BasicNode.h"
#include <iostream>

BasicNode::BasicNode(int ID, float x_, float y_, float z_, int t, float a, float dw): nodeID(ID), x(x_), y(y_), z(z_), type(t), area(a), doorwidth(dw) {}

void BasicNode::print() {
	std::cout << nodeID << ": (" << x << "," << y << "," << z << ") Type: " << type << " Area: " << area << " Door width: " << doorwidth << std::endl;
}
