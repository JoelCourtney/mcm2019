#include "Setup/Setup.h"
#include <stdlib.h>

NaiveSetup::NaiveSetup(BasicGraph bg_) : Setup(bg_) {}


Graph NaiveSetup::createInitialConditions() {
	people = 5000;
	Graph g = bg.buildGraph();
	for (int i = 0; i < people; i++) {
		int nodeID = rand()%468;
		g.getNode(nodeID)->enter(new Tourist(0));
	}
	return g;
}
