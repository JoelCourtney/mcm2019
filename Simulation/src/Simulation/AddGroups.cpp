#include "Simulation/Simulation.h"
#include <random>
#include "Constants.h"

AddGroups::AddGroups(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph AddGroups::createInitialConditions(int target, int stairWait) {
	//for (int i = 0; i < edges.size(); i++) {
		//EdgeLine e = edges.at(i);
		//if (nodes.at(e.fromID).type == -2 && nodes.at(e.toID).type == -2) {
			//edges.erase(edges.begin() + i);
			//i--;
		//}
	//}
	people = 0;
	BasicGraph bg = buildBasicGraph();
	Graph g = bg.buildGraph(stairWait);
	int groupID = 1;
	while (people < target) {
		int num;
		int r = rand()%6;
		if (r == 0) num = 1;
		else if (r == 1 || r == 2 || r == 3) num = rand()%3 + 2;
		else if (r == 4) num = rand()%3+1;
		 else if (r == 5) num = rand()%15 + 1;
		if (num == 1) g.getNode(rand()%NUM_NODES)->enter(new Tourist(0));
		else {
			int nodeID = rand()%NUM_NODES;
			Node* node = g.getNode(nodeID);
			for (int i = 0; i < num; i++) {
				node->enter(new Tourist(groupID));
			}
			groupID++;
		}
		people += num;
	}
	return g;
}

void AddGroups::perturb(Graph& g, int tick) {}
