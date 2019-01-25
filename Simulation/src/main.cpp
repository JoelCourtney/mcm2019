#include <iostream>
#include "BasicGraph.h"
#include <iostream>
#include "Graph.h"

int main() {
	BasicNode n1(1.0, -1.0, 2);
	BasicNode n2(-1.5,0,0);

	BasicGraph louvre;
	louvre.addNode(n1);
	louvre.addNode(n2);

	BasicEdge e1(10, 3, 5, EdgeType::Normal, louvre.getNode(0), louvre.getNode(1));

	louvre.addEdge(e1);

	std::cout << louvre.getNode(0)->adj.at(0)->to->x << std::endl;
};
