#include "Graph.h"

void Graph::addNode(Node n) {
	nodes.push_back(n);
}

void Graph::addEdge(Edge e) {
	edges.push_back(e);
	e.from->adj.push_back(&edges.back());
	e.to->adj.push_back(&edges.back());
}

Node* Graph::getNode(int i) {
	return &nodes.at(i);
}
