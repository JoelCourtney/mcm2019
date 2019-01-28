#include "Setup/Setup.h"
#include <random>
#include "Constants.h"

AddWheelchairs::AddWheelchairs(std::vector<NodeLine> n, std::vector<EdgeLine> e) : Setup(n,e) {}

Graph AddWheelchairs::createInitialConditions() {
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
	while (people < TARGET_PEOPLE) {
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
				g.getNode(rand()%NUM_NODES)->enter(new DisabledTourist(0));
			}
		} else {
			int nodeID = rand()%NUM_NODES;
			Node* node = g.getNode(nodeID);
			for (int i = 0; i < num; i++) {
				if (rand()%100<99)
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
