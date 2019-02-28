#include "Simulation/Simulation.h"
#include <stdlib.h>
#include "Constants.h"

NaiveSimulation::NaiveSimulation(std::vector<NodeLine> n,std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph NaiveSimulation::createInitialConditions(int target, int stairWait) {
	people = target;
	BasicGraph bg = buildBasicGraph();
	Graph g = bg.buildGraph(stairWait);
	for (int i = 0; i < people; i++) {
		int nodeID = rand()%NUM_NODES;
		g.getNode(nodeID)->enter(new Tourist(0));
	}
	return g;
}

void NaiveSimulation::perturb(Graph& g, int tick) {}
