#include "Setup/Setup.h"
#include <stdlib.h>
#include "Constants.h"

NaiveSetup::NaiveSetup(std::vector<NodeLine> n,std::vector<EdgeLine> e) : Setup(n,e) {}


Graph NaiveSetup::createInitialConditions() {
	people = TARGET_PEOPLE;
	BasicGraph bg = buildBasicGraph();
	Graph g = bg.buildGraph();
	for (int i = 0; i < people; i++) {
		int nodeID = rand()%NUM_NODES;
		g.getNode(nodeID)->enter(new Tourist(0));
	}
	return g;
}
