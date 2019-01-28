#include "Simulation/Simulation.h"
#include <random>
#include "Constants.h"

AddBias::AddBias(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph AddBias::createInitialConditions(int target) {
	//for (int i = 0; i < edges.size(); i++) {
		//EdgeLine e = edges.at(i);
		//if (nodes.at(e.fromID).type == -2 && nodes.at(e.toID).type == -2) {
			//edges.erase(edges.begin() + i);
			//i--;
		//}
	//}
	people = 0;
	BasicGraph bg = buildBasicGraph();

	//bg.getNode(45)->dangerous = true;
	int count = 0;
	while (count < 5) {
		int r = rand()%NUM_NODES;
		BasicNode* bn = bg.getNode(r);
		if (bn->type > 0) {
			count++;
			bn->dangerous = true;
		}
	}

	Graph g = bg.buildGraph();
	int groupID = 1;
	while (people < target) {
		Node* node;
		if (rand() % 4 == 0) {
			int specials[] = {262, 366, 228, 288, 450, 400, 416, 422, 129, 150, 172, 195, 50, 56, 68};
			node = g.getNode(specials[rand()%15]);
		} else {
			node = g.getNode(rand()%NUM_NODES);
		}
		int num;
		int r = rand()%5;
		if (r == 0) num = 1;
		else if (r == 1 || r == 2) num = rand()%3 + 1;
		else if (r == 3) num = rand()%7 + 1;
 		else if (r == 4) num = rand()%15 + 1;
		if (num == 1) {
			if (rand()%100<=99)
				node->enter(new Tourist(0));
			else {
				node->enter(new Police());
			}
		} else {
			for (int i = 0; i < num; i++) {
				if (rand()%100<=99)
					node->enter(new Tourist(groupID));
				else
					node->enter(new DisabledTourist(groupID));
			}
			groupID++;
		}
		people += num;
	}
	return g;
}

void AddBias::perturb(Graph& g, int tick) {}
