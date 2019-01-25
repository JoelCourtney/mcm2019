#include <iostream>
#include "Graph.h"
#include <iostream>

int main() {
	Node n1(1.0, -1.0, 2);
	Node n2(-1.5,0,0);

	Graph louvre;
	louvre.addNode(n1);
	louvre.addNode(n2);

	Edge e1(10, 3, 5, EdgeType::Normal, louvre.getNode(0), louvre.getNode(1));

	std::cout << louvre.getNode(0)->adj.at(0)->to->x << std::endl;
};
