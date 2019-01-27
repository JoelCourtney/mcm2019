#pragma once

#include <vector>
#include "Node.h"
#include "Door.h"

class Graph {
	std::vector<Node*> nodes;
	std::vector<Door*> doors;

public:
	~Graph();

	void addNode(Node*);
	void addDoor(Door*);

	Node* getNode(int);

	std::vector<int> update();

	void print();
	void printExits();
	int getExited();
};
