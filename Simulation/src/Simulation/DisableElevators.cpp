#include "Constants.h"
#include "Simulation/Simulation.h"

DisableElevators::DisableElevators(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph DisableElevators::createInitialConditions(int target) {
	for (int i = 0; i < edges.size(); i++) {
		EdgeLine e = edges.at(i);
		if (nodes.at(e.fromID).type == -2 && nodes.at(e.toID).type == -2) {
			edges.erase(edges.begin() + i);
			i--;
		}
	}
	people = target;
	BasicGraph bg = buildBasicGraph();
	Graph g = bg.buildGraph();
	for (int i = 0; i < people; i++) {
		int nodeID = rand()%NUM_NODES;
		g.getNode(nodeID)->enter(new Tourist(0));
	}
	return g;
}

void DisableElevators::perturb(Graph& g, int tick) {}
