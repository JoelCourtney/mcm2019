#include "Simulation/Simulation.h"
#include <random>
#include "Constants.h"

AddExits::AddExits(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Simulation(n,e) {}

Graph AddExits::createInitialConditions(int target, int stairWait) {
	//for (int i = 0; i < edges.size(); i++) {
		//EdgeLine e = edges.at(i);
		//if (nodes.at(e.fromID).type == -2 && nodes.at(e.toID).type == -2) {
			//edges.erase(edges.begin() + i);
			//i--;
		//}
	//}
	int exits = 2;
	people = 0;
	BasicGraph bg = buildBasicGraph();
	for (int i = 0; i < exits; i++) {
		int from = rand()%225;
		int to = nodes.size();
		EdgeLine e;
		e.fromID = from;
		e.toID = to;
		edges.push_back(e);
		NodeLine n;
		std::cout << "making " << to << std::endl;
		n.nodeID = to;
		n.x = 0;
		n.y = 0;
		n.z = 0;
		n.type = 0;
		n.area = 0;
		n.doorwidth = 0;
		nodes.push_back(n);
	}

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

	Graph g = bg.buildGraph(stairWait);
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

void AddExits::perturb(Graph& g, int tick) {
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
