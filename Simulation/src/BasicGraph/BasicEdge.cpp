#include "BasicGraph/BasicEdge.h"
#include <iostream>

BasicEdge::BasicEdge(BasicNode* from_, BasicNode* to_) : from(from_), to(to_) {}

void BasicEdge::print() {
	std::cout << from->nodeID << "->" << to->nodeID << std::endl;
}
