#include <iostream>
#include "BasicGraph/BasicGraph.h"
#include <iostream>
#include "Graph/Graph.h"

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
	Escalator* e = new Escalator(0,0,0,0,5,5);
	Exit* m = new Exit(1, 1, 2, 0);
	Door* d1 = new Door(3);
	Door* d2 = new Door(3);
	Passage p1(d1, e);
	Passage p2(d2, m);
	Directions dir1;
	dir1.normal = p1;
	Directions dir2;
	dir2.normal = p2;
	n->setDirections(dir1);
	e->setDirections(dir2);

	Graph g;
	g.addNode(m);
	g.addNode(n);
	g.addNode(e);
	g.addDoor(d1);
	g.addDoor(d2);

	Tourist* t1 = new Tourist(1);
	Tourist* t2 = new Tourist(1);
	Tourist* t3 = new Tourist(1);
	n->enter(t1);
	n->enter(t2);
	n->enter(t3);

	g.print();
	for (int i = 0; i < 20; i++) {
		g.update();
		g.print();
	}
};
