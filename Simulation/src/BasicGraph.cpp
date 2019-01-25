#include "BasicGraph.h"

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
