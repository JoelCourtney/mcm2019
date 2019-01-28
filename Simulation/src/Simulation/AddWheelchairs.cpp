#include "Simulation/Simulation.h"
#include <random>
#include "Constants.h"

AddWheelchairs::AddWheelchairs(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph AddWheelchairs::createInitialConditions(int target) {
	//for (int i = 0; i < edges.size(); i++) {
		//EdgeLine e = edges.at(i);
		//if (nodes.at(e.fromID).type == -2 && nodes.at(e.toID).type == -2) {
			//edges.erase(edges.begin() + i);
			//i--;
		//}
	//}
	people = 0;
	BasicGraph bg = buildBasicGraph();
	Graph g = bg.buildGraph();
	int groupID = 1;
	while (people < target) {
		int num;
		int r = rand()%5;
		if (r == 0) num = 1;
		else if (r == 1 || r == 2) num = rand()%3 + 1;
		else if (r == 3) num = rand()%7 + 1;
 		else if (r == 4) num = rand()%15 + 1;
		if (num == 1) {
			if (rand()%100<99)
				g.getNode(rand()%NUM_NODES)->enter(new Tourist(0));
			else {
				int r = rand()%NUM_NODES;
				BasicNode* bn = bg.getNode(rand()%NUM_NODES);
				while (bn->type != 0) {
					r = rand()%NUM_NODES; bn = bg.getNode(rand()%NUM_NODES);
				}
				g.getNode(r)->enter(new DisabledTourist(0));
			}
		} else {
			int nodeID = rand()%NUM_NODES;
			Node* node = g.getNode(nodeID);
			for (int i = 0; i < num; i++) {
				if (rand()%100<99)
					node->enter(new Tourist(groupID));
				else {
					int r = rand()%NUM_NODES;
					BasicNode* bn = bg.getNode(rand()%NUM_NODES);
					while (bn->type != 0) {
						r = rand()%NUM_NODES;
						bn = bg.getNode(rand()%NUM_NODES);
					}
					std::cout << bn->type;
					g.getNode(r)->enter(new DisabledTourist(groupID));
				}
			}
			groupID++;
		}
		people += num;
	}
	return g;
}

void AddWheelchairs::perturb(Graph& g, int tick) {}
