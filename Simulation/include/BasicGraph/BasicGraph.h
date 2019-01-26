#pragma once

#include <vector>
#include "BasicNode.h"
#include "BasicEdge.h"

class BasicGraph {
	std::vector<BasicNode> nodes;
	std::vector<BasicEdge> edges;

public:
	void addNode(BasicNode);
	void addEdge(BasicEdge);

	BasicNode* getNode(int);
};
