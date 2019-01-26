#pragma once

#include <vector>
#include <string>
#include "BasicNode.h"
#include "BasicEdge.h"
#include "Graph/Graph.h"

class BasicGraph {
	std::vector<BasicNode> nodes;
	std::vector<BasicEdge> edges;

	std::vector<std::tuple<int,int,int>> findPaths();
	std::vector<std::tuple<int,float>> dijkstra(int,bool);

public:
	void addNode(BasicNode);
	void addEdge(BasicEdge);

	int getIndexOfNode(int);
	BasicNode* getNode(int);

	Graph buildGraph();

	void print();
};
