#include "Simulation/Simulation.h"
#include <random>
#include "Constants.h"

AddDanger::AddDanger(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph AddDanger::createInitialConditions(int target) {
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
			dangerNodes.push_back(r);
		}
	}

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
			if (rand()%100<=99)
				g.getNode(rand()%NUM_NODES)->enter(new Tourist(0));
			else {
				g.getNode(rand()%NUM_NODES)->enter(new Police());
				countPolice++;
			}
		} else {
			int nodeID = rand()%NUM_NODES;
			Node* node = g.getNode(nodeID);
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

void AddDanger::perturb(Graph& g, int tick) {
	//if (tick > 400 && tick < 600) {
		//if (tick % 15 == 0) {
			//std::cout << "heloo\n";
			//int r = rand() % 225;
			//Node* n = g.getNode(r);
			//n->enter(new Police());
			//countPolice++;
		//}
	if (tick > 1100 && countPolice > 0) {
		int count = 0;
		for (int i = 0; i < dangerNodes.size(); i++) {
			count += g.getNode(dangerNodes.at(i))->getExited();
		}
		std::cout << countPolice-count << std::endl;
		if (count == countPolice) {
			countPolice = -1;
			std::cout << "Police all arrived within " << tick << " ticks." << std::endl;
		}
	}
}
