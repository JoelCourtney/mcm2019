#include "BasicGraph/BasicEdge.h"
#include <iostream>
#include <math.h>

BasicEdge::BasicEdge(int from_, int to_) : fromID(from_), toID(to_) {}

void BasicEdge::print() {
	std::cout << fromID << "->" << toID << " Distance: " << distance << std::endl;
}
