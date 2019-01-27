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
	float dz = from.z - to.z;
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
	for (int i = 0; i < edges.size(); i++) {
		edges.at(i).print();
	}
}

std::vector<std::tuple<int,int,int>> BasicGraph::findPaths() {
	std::vector<std::vector<std::tuple<int,float>>> choices;
	std::vector<std::vector<std::tuple<int,float>>> disabledChoices;
	std::vector<std::vector<std::tuple<int,float>>> policeChoices;
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.at(i).type == BasicNodeType::Exit) {
			choices.push_back(dijkstra(i, false));
			disabledChoices.push_back(dijkstra(i, true));
		} else if (nodes.at(i).type == BasicNodeType::Danger) {
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
		results.push_back(std::tuple<int,int,int>(choice,disabledChoice,policeChoice));
	}
	return results;
}

std::vector<std::tuple<int,float>> BasicGraph::dijkstra(int start, bool disabled) {
	std::vector<int> distances(nodes.size(),10000000);
	std::vector<int> paths(nodes.size(),-1);
	distances.at(start) = 0;
	paths.at(start) = -2;
	for (int i = 0; i < nodes.size() - 1; i++) {
		float lowest = 10000000000000;
		int lowestTo = -1;
		int lowestFrom = -1;
		for (int j = 0; j < nodes.size(); j++) {
			if (paths.at(j) != -1) {
				BasicNode cursor = nodes.at(j);
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
		if (lowestFrom == -1) {
			std::cout << "Graph is disconnected starting from " << start+1 << std::endl;
			std::cout << "Untouched nodes:\n";
			for (int j = 0; j < paths.size(); j++) {
				if (paths.at(j) == -1) {
					std::cout << j+1 << std::endl;
					}
			}
			exit(-1);
		}
		distances.at(lowestFrom) = distances.at(lowestTo) + lowest;
		paths.at(lowestFrom) = lowestTo;
	}
	std::vector<std::tuple<int,float>> result;
	for (int i = 0; i < distances.size(); i++) {
		result.push_back(std::tuple<int,float>(paths.at(i),distances.at(i)));
	}
	return result;
}

Graph BasicGraph::buildGraph() {
	Graph g;
	for (int i = 0; i < nodes.size(); i++) {
		BasicNode bn = nodes.at(i);
		if (bn.type > 0) {
			Exhibit* e = new Exhibit(bn.nodeID,(int)(bn.area/bn.type));
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Exit) {
			Exit* e = new Exit(bn.nodeID);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Escalator) {
			Escalator* e = new Escalator(bn.nodeID,bn.area,20);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Elevator || bn.type == BasicNodeType::DisabledElevator) {
			Elevator* e = new Elevator(bn.nodeID,8,20);
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
		} else if (std::get<0>(paths.at(to.nodeID)) == from.nodeID) {
			disabledChoice = -1;
		} else {
			disabledChoice = 0;
		}
		if (std::get<2>(paths.at(from.nodeID)) == to.nodeID) {
			policeChoice = 1;
		} else if (std::get<0>(paths.at(to.nodeID)) == from.nodeID) {
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
		std::cout << "From: " << from.nodeID << " To: " << to.nodeID << " | " << fromDoors << "," << toDoors << std::endl;
		Node* fromPrev = start;
		Room* r;
		Door* d;
		Passage backward;
		Passage forward;
		for (int j = 0; j < fromDoors; j++) {
			r = new Room(nodeNumber++, from.area/from.type);
			d = new Door(from.doorwidth);
			backward = Passage(d,fromPrev);
			forward = Passage(d,r);
			r->addPassage(backward);
			fromPrev->addPassage(forward);
			if (normalChoice == 1) {
				fromPrev->changePreference(0);
			} else {
				r->changePreference(0);
			}
			if (disabledChoice == 1) {
				fromPrev->changePreference(1);
			} else {
				r->changePreference(1);
			}
			if (policeChoice == 1) {
				fromPrev->changePreference(2);
			} else {
				r->changePreference(2);
			}
			static_cast<Exhibit*>(start)->addRoom(r);
			g.addNode(r);
			g.addDoor(d);
			fromPrev = r;
		}
		Node* toPrev = end;
		for (int j = 0; j < toDoors; j++) {
			r = new Room(nodeNumber++, to.area/to.type);
			d = new Door(to.doorwidth);
			backward = Passage(d,toPrev);
			forward = Passage(d,r);
			r->addPassage(backward);
			toPrev->addPassage(forward);
			if (normalChoice == -1) {
				fromPrev->changePreference(0);
			} else {
				r->changePreference(0);
			}
			if (disabledChoice == -1) {
				fromPrev->changePreference(1);
			} else {
				r->changePreference(1);
			}
			if (policeChoice == -1) {
				fromPrev->changePreference(2);
			} else {
				r->changePreference(2);
			}
			static_cast<Exhibit*>(end)->addRoom(r);
			g.addNode(r);
			g.addDoor(d);
			toPrev = r;
		}
		d = new Door((from.doorwidth + to.doorwidth)/2);
		backward = Passage(d,fromPrev);
		forward = Passage(d,toPrev);
		toPrev->addPassage(backward);
		fromPrev->addPassage(forward);
		if (normalChoice == 1) {
			fromPrev->changePreference(0);
		} else if (normalChoice == -1) {
			toPrev->changePreference(0);
		}
		if (disabledChoice == 1) {
			fromPrev->changePreference(1);
		} else if (disabledChoice == -1) {
			toPrev->changePreference(1);
		}
		if (policeChoice == 1) {
			fromPrev->changePreference(2);
		} else if (policeChoice == -1) {
			toPrev->changePreference(2);
		}
		g.addDoor(d);
	}
	return g;
}
