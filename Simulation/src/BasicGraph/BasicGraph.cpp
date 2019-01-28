#include "BasicGraph/BasicGraph.h"
#include <iostream>
#include <math.h>

void BasicGraph::addNode(BasicNode n) {
	for (int i = 0; i < nodes.size(); i++) {
		if (n.nodeID < nodes.at(i).nodeID) {
			nodes.insert(nodes.begin() + i, n);
			return;
		}
	}
	nodes.push_back(n);
}

void BasicGraph::addEdge(BasicEdge e) {
	BasicNode from = nodes.at(e.fromID);
	BasicNode to = nodes.at(e.toID);
	float dx = from.x - to.x;
	float dy = from.y - to.y;
	float dz = 10*(from.z - to.z);
	e.distance = sqrt(dx*dx + dy*dy + dz*dz);
	edges.push_back(e);
	nodes.at(e.fromID).adj.push_back(edges.size()-1);
	nodes.at(e.toID).adj.push_back(edges.size()-1);
}

int BasicGraph::getIndexOfNode(int n) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.at(i).nodeID == n) {
			return i;
		}
	}
	std::cout << "Node " << n << " not found.\n";
	exit(-2);
}

BasicNode* BasicGraph::getNode(int i) {
	return &(*(nodes.begin()+i));
}

void BasicGraph::print() {
	std::cout << "Nodes:" << std::endl;
	for (int i = 0; i < nodes.size(); i++) {
		nodes.at(i).print();
	}
	std::cout << "\nEdges:\n";
	float count = 0;
	for (int i = 0; i < edges.size(); i++) {
		edges.at(i).print();
		count += edges.at(i).distance;
	}
	std::cout << count << std::endl;
}

std::vector<std::tuple<int,int,int>> BasicGraph::findPaths() {
	std::vector<std::vector<std::tuple<int,float>>> choices;
	std::vector<std::vector<std::tuple<int,float>>> disabledChoices;
	std::vector<std::vector<std::tuple<int,float>>> policeChoices;
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.at(i).type == BasicNodeType::Exit) {
			choices.push_back(dijkstra(i, false));
			disabledChoices.push_back(dijkstra(i, true));
		} else if (nodes.at(i).dangerous) {
			policeChoices.push_back(dijkstra(i,false));
		} else {
			continue;
		}
	}
	std::vector<std::tuple<int,int,int>> results;
	for (int i = 0; i < nodes.size(); i++) {
		int choice = -1;
		float dist = 1000000000;
		for (int j = 0; j < choices.size(); j++) {
			std::tuple<int,float> path = choices.at(j).at(i);
			if (std::get<1>(path) < dist) {
				choice = std::get<0>(path);
				dist = std::get<1>(path);
			}
		}

		int disabledChoice = -1;
		dist = 1000000000;
		for (int j = 0; j < disabledChoices.size(); j++) {
			std::tuple<int,float> path = disabledChoices.at(j).at(i);
			if (std::get<1>(path) < dist) {
				disabledChoice = std::get<0>(path);
				dist = std::get<1>(path);
			}
		}

		int policeChoice = -1;
		dist = 1000000000;
		for (int j = 0; j < policeChoices.size(); j++) {
			std::tuple<int,float> path = policeChoices.at(j).at(i);
			if (std::get<1>(path) < dist) {
				policeChoice = std::get<0>(path);
				dist = std::get<1>(path);
			}
		}
		//std::vector<int> asdf = {149,110};
		//for (int j = 0; j < asdf.size(); j++) {
			//if (asdf.at(j) == i)
				//std::cout << "Choice at :" << i << " is " << disabledChoice << std::endl;
		//}
		results.push_back(std::tuple<int,int,int>(choice,disabledChoice,policeChoice));
	}
	return results;
}

std::vector<std::tuple<int,float>> BasicGraph::dijkstra(int start, bool disabled) {
	bool avoidDanger = !(nodes.at(start).dangerous);
	std::vector<float> distances(nodes.size(),10000000000);
	std::vector<int> paths(nodes.size(),-1);
	distances.at(start) = 0;
	paths.at(start) = -2;
	for (int i = 0; i < nodes.size() - 1; i++) {
		float lowest = 100000000000;
		int lowestTo = -1;
		int lowestFrom = -1;
		for (int j = 0; j < nodes.size(); j++) {
			if (paths.at(j) != -1) {
				BasicNode cursor = nodes.at(j);
				//if (cursor.type == -3) std::cout << cursor.nodeID << std::endl;
				if ((disabled && (cursor.type != -1)) || ((!disabled) && cursor.type != -3)) {
				//if (cursor.type != -3) {
					for (int k = 0; k < cursor.adj.size(); k++) {
						int other;
						BasicEdge e = edges.at(cursor.adj.at(k));
						if (e.toID == j) {
							other = e.fromID;
						} else {
							other = e.toID;
						}
						if (paths.at(other) == -1 && e.distance+distances.at(j) < lowest) {
							lowest = e.distance + distances.at(j);
							lowestTo = j;
							lowestFrom = other;
						}
					}
				}
			}
		}
		if (lowestTo == -1) {
			std::cout << "Graph is disconnected starting from " << start+1  << "as " << disabled << std::endl;
			std::cout << "Untouched nodes:\n";
			for (int j = 0; j < paths.size(); j++) {
				if (paths.at(j) == -1) {
					std::cout << j+1 << std::endl;
				}
			}
			exit(-1);
		}
		distances.at(lowestFrom) = lowest;
		paths.at(lowestFrom) = lowestTo;
	}
	std::vector<std::tuple<int,float>> result;
	for (int i = 0; i < distances.size(); i++) {
		result.push_back(std::tuple<int,float>(paths.at(i),distances.at(i)));
	}
	//if (!disabled && start != 0) {
		//std::cout << "searching from " << start<< std::endl;
		//for (int i = 0; i < distances.size(); i++) {
			//std::cout << paths.at(i) << " ";
		//}
	//}
	return result;
}

Graph BasicGraph::buildGraph(int stairWait) {
	Graph g;
	for (int i = 0; i < nodes.size(); i++) {
		BasicNode bn = nodes.at(i);
		if (bn.type > 0) {
			float a = bn.area/bn.type;
			int cap = (a/9 > 2)?a/9:2;
			Exhibit* e;
			if (!bn.dangerous)
				e = new Exhibit(bn.nodeID,cap);
			else {
				e = new Danger(bn.nodeID,cap);
			}
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Exit) {
			Exit* e = new Exit(bn.nodeID);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Escalator) {
			Escalator* e = new Escalator(bn.nodeID,bn.doorwidth,stairWait);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Elevator || bn.type == BasicNodeType::DisabledElevator) {
			Elevator* e = new Elevator(bn.nodeID,6,20);
			g.addNode(e);
		}
	}
	std::vector<std::pair<int,int>> doorsLeft(nodes.size());
	for (int i = 0; i < nodes.size(); i++) {
		doorsLeft.at(i) = std::pair<int,int>(nodes.at(i).type-1,nodes.at(i).adj.size());
	}
	auto paths = findPaths();
	int nodeNumber = nodes.back().nodeID + 1;
	for (int i = 0; i < edges.size(); i++) {
		BasicEdge e = edges.at(i);
		BasicNode from = nodes.at(e.fromID);
		BasicNode to = nodes.at(e.toID);
		Node* start = g.getNode(from.nodeID);
		Node* end = g.getNode(to.nodeID);
		int normalChoice, disabledChoice, policeChoice;
		if (std::get<0>(paths.at(from.nodeID)) == to.nodeID) {
			normalChoice = 1;
		} else if (std::get<0>(paths.at(to.nodeID)) == from.nodeID) {
			normalChoice = -1;
		} else {
			normalChoice = 0;
		}
		if (std::get<1>(paths.at(from.nodeID)) == to.nodeID) {
			disabledChoice = 1;
		} else if (std::get<1>(paths.at(to.nodeID)) == from.nodeID) {
			disabledChoice = -1;
		} else {
			disabledChoice = 0;
		}
		if (std::get<2>(paths.at(from.nodeID)) == to.nodeID) {
			policeChoice = 1;
		} else if (std::get<2>(paths.at(to.nodeID)) == from.nodeID) {
			policeChoice = -1;
		} else {
			policeChoice = 0;
		}
		int fromDoors = 0;
		if (from.type > 0) {
			auto fromPair = doorsLeft.at(e.fromID);
			fromDoors = fromPair.first / fromPair.second;
			doorsLeft.at(e.fromID) = std::pair<int,int>(fromPair.first-fromDoors,fromPair.second-1);
		}
		int toDoors = 0;
		if (to.type > 0) {
			auto toPair = doorsLeft.at(e.toID);
			toDoors = toPair.first / toPair.second;
			doorsLeft.at(e.toID) = std::pair<int,int>(toPair.first-toDoors,toPair.second-1);
		}
		std::vector<Node*> rooms;
		rooms.push_back(start);
		std::vector<Door*> doors;
		for (int i = 0; i < fromDoors; i++) {
			rooms.push_back(new Room(nodeNumber++, from.area/from.type));
			doors.push_back(new Door(from.doorwidth));
		}
		doors.push_back(new Door((from.doorwidth + to.doorwidth)/2));
		for (int i = 0; i < toDoors; i++) {
			rooms.push_back(new Room(nodeNumber++, to.area/to.type));
			doors.push_back(new Door(to.doorwidth));
		}
		rooms.push_back(end);
		for (int i = 0; i < doors.size(); i++) {
			Passage forward(doors.at(i),rooms.at(i+1));
			Passage backward(doors.at(i),rooms.at(i));
			rooms.at(i)->addPassage(forward);
			rooms.at(i+1)->addPassage(backward);
			if (normalChoice == 1) rooms.at(i)->changePreference(0);
			else if (normalChoice == -1) rooms.at(i+1)->changePreference(0);
			else if (i < fromDoors) rooms.at(i+1)->changePreference(0);
			else if (i > fromDoors) rooms.at(i)->changePreference(0);

			if (disabledChoice == 1) rooms.at(i)->changePreference(1);
			else if (disabledChoice == -1) rooms.at(i+1)->changePreference(1);
			else if (i < fromDoors) rooms.at(i+1)->changePreference(1);
			else if (i > fromDoors) rooms.at(i)->changePreference(1);

			if (policeChoice == 1) rooms.at(i)->changePreference(2);
			else if (policeChoice == -1) rooms.at(i+1)->changePreference(2);
			else if (i < fromDoors) rooms.at(i+1)->changePreference(2);
			else if (i > fromDoors) rooms.at(i)->changePreference(2);
		}
		g.addDoor(doors.at(0));
		for (int i = 1; i < doors.size(); i++) {
			g.addNode(rooms.at(i));
			g.addDoor(doors.at(i));
		}
	}
	return g;
}
