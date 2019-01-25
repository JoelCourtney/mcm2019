#pragma once

#include <vector>
#include "BasicGraph.h"
#include "Node.h"
#include "Door.h"

class Graph {
	std::vector<Node> nodes;
	std::vector<Door> doors;
};
