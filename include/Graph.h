#pragma once

#include <vector>
#include "Node.h"
#include "Edge.h"

class Graph {
	std::vector<Node> nodes;
	std::vector<Edge> edges;

public:
	void addNode(Node);
	void addEdge(Edge);

	Node* getNode(int);
};
