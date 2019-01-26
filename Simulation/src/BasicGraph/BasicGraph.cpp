#include "BasicGraph/BasicGraph.h"
#include <iostream>

void BasicGraph::addNode(BasicNode n) {
	nodes.push_back(n);
}

void BasicGraph::addEdge(BasicEdge e) {
	edges.push_back(e);
	e.from->adj.push_back(&edges.back());
	e.to->adj.push_back(&edges.back());
}

BasicNode* BasicGraph::getNode(int i) {
	return &nodes.at(i);
}

void BasicGraph::print() {
	std::cout << "Nodes:" << std::endl;
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i).print();
	}
	std::cout << "\nEdges:\n";
	for (int i = 0; i < edges.size(); i++) {
		edges.at(i).print();
	}
}

Graph BasicGraph::buildGraph() {
	Graph g;
	for (int i = 0; i < nodes.size(); i++) {
		BasicNode bn = nodes.at(i);
		if (bn.type > 0) {
			Exhibit* e = new Exhibit(bn.nodeID,bn.x,bn.y,bn.z,(int)(bn.area/bn.nrooms));
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Exit) {
			Exit* e = new Exit(bn.nodeID,bn.x,bn.y,bn.z);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Escalator) {
			Escalator* e = new Escalator(bn.nodeID,bn.x,bn.y,bn.z,bn.area,20);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Elevator || bn.type == BasicNodeType::DisabledElevator) {
			Elevator* e = new Elevator(bn.nodeID,bn.x,bn.y,bn.z,8,20);
			g.addNode(e);
		}
	}
	return g;
}
