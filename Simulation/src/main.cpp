#include <iostream>
#include "BasicGraph.h"
#include <iostream>
#include "Graph.h"

int main() {
	//BasicNode n1(1.0, -1.0, 2);
	//BasicNode n2(-1.5,0,0);

	//BasicGraph louvre;
	//louvre.addNode(n1);
	//louvre.addNode(n2);

	//BasicEdge e1(10, 3, 5, EdgeType::Normal, louvre.getNode(0), louvre.getNode(1));

	//louvre.addEdge(e1);

	/////////////
	
	Exhibit* n = new Exhibit(0, 0, 0, 0, 10);
	Exit* m = new Exit(1, 1, 2, 0);
	Door* d = new Door(2);
	Passage p(d, m);
	Directions dir;
	dir.normal = p;
	n->setDirections(dir);

	Graph g;
	g.addNode(m);
	g.addNode(n);
	g.addDoor(d);

	Tourist* t1 = new Tourist();
	Tourist* t2 = new Tourist();
	Tourist* t3 = new Tourist();
	n->enter(t1);
	n->enter(t2);
	n->enter(t3);

	g.print();
	g.update();
	g.print();
	g.update();
	g.print();
	g.update();
	g.print();
};
