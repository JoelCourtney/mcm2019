#pragma once

#include <vector>
#include <string>
#include "BasicNode.h"
#include "BasicEdge.h"
#include "Graph/Graph.h"

class BasicGraph {
	std::vector<BasicNode> nodes;
	std::vector<BasicEdge> edges;

public:
	void addNode(BasicNode);
	void addEdge(BasicEdge);

	BasicNode* getNode(int);

	Graph buildGraph();

	void print();
};
