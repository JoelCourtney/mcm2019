#include "Graph/Graph.h"
#include <iostream>
#include "Constants.h"

Graph::~Graph() {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes.at(i);
	}
	for (int i = 0; i < doors.size(); i++) {
		delete doors.at(i);
	}
}

std::vector<int> Graph::update() {
	std::vector<int> data;
	data.reserve(NUM_NODES);
	for (int i = 0; i < nodes.size(); i++) {
		int count = nodes.at(i)->update();
		if (i < NUM_NODES) data.push_back(count);
	}
	for (int i = 0; i < doors.size(); i++) {
		doors.at(i)->reset();
	}
	return data;
}

void Graph::addNode(Node* n) {
	nodes.push_back(n);
}

void Graph::addDoor(Door* d) {
	doors.push_back(d);
}

Node* Graph::getNode(int n) {
	return nodes.at(n);
}

void Graph::print() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->print();
	}
}

void Graph::printExits() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->printExit();
	}
}

int Graph::getExited() {
	int count = 0;
	for (int i = 0; i < nodes.size(); i++) {
		count += nodes.at(i)->getExited();
	}
	return count;
}
