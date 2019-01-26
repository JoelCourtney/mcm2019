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
				dist = std::get<0>(path);
			}
		}
		int disabledChoice = -1;
		dist = 1000000000;
		for (int j = 0; j < disabledChoices.size(); j++) {
			std::tuple<int,float> path = disabledChoices.at(j).at(i);
			if (std::get<1>(path) < dist) {
				disabledChoice = std::get<0>(path);
				dist = std::get<0>(path);
			}
		}
		int policeChoice = -1;
		dist = 1000000000;
		for (int j = 0; j < policeChoices.size(); j++) {
			std::tuple<int,float> path = policeChoices.at(j).at(i);
			if (std::get<1>(path) < dist) {
				policeChoice = std::get<0>(path);
				dist = std::get<0>(path);
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
		float lowest = 1000000000;
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
			std::cout << "Graph is disconnected." << std::endl;
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
			Exhibit* e = new Exhibit(bn.nodeID,bn.x,bn.y,bn.z,(int)(bn.area/bn.type));
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Exit) {
			Exit* e = new Exit(bn.nodeID,bn.x,bn.y,bn.z);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Escalator) {
			Escalator* e = new Escalator(bn.nodeID,bn.x,bn.y,bn.z,bn.area,20);
			g.addNode(e);
		} else if (bn.type == BasicNodeType::Elevator || bn.type == BasicNodeType::DisabledElevator) {
			Elevator* e = new Elevator(bn.nodeID,bn.x,bn.y,bn.z,8,20);
			g.addNode(e);
		}
	}
	auto paths = findPaths();
	for (int i = 0; i < paths.size(); i++) {
		auto t = paths.at(i);
		std::cout << std::get<0>(t) << ","<<std::get<1>(t) << "," << std::get<2>(t)<<std::endl;
	}
	std::cout << std::endl;
	return g;
}
