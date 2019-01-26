#include "Graph/Graph.h"
#include <iostream>

Graph::~Graph() {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes.at(i);
	}
	for (int i = 0; i < doors.size(); i++) {
		delete doors.at(i);
	}
}

void Graph::update() {
	for (int i = nodes.size() - 1; i >= 0; i--) {
		nodes.at(i)->update();
	}
	for (int i = 0; i < doors.size(); i++) {
		doors.at(i)->reset();
	}
}


void Graph::addNode(Node* n) {
	nodes.push_back(n);
}

void Graph::addDoor(Door* d) {
	doors.push_back(d);
}

void Graph::print() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i)->print();
	}
}
