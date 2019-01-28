#include "Setup/Setup.h"
#include "CSV/Lines.h"

Setup::Setup(std::vector<NodeLine> n,std::vector<EdgeLine> e) : nodes(n), edges(e) {}

int Setup::peopleAdded() {
	return people;
}

BasicGraph Setup::buildBasicGraph() {
	BasicGraph bg;
	for (int i = 0; i < nodes.size(); i++) {
		NodeLine line = nodes.at(i);
		BasicNode n(
			line.nodeID,
			line.x,
			line.y,
			line.z,
			line.type,
			line.area,
			line.doorwidth
		);
		bg.addNode(n);
	}
	for (int i = 0; i < edges.size(); i++) {
		EdgeLine line = edges.at(i);
		BasicEdge e(
			line.fromID,
			line.toID
		);
		bg.addEdge(e);
	}
	return bg;
}
