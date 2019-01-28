#pragma once

#include <random>
#include <iostream>
#include "Graph/Graph.h"
#include "BasicGraph/BasicGraph.h"
#include "CSV/Lines.h"

class Simulation {
protected:
	int people;
	std::vector<NodeLine> nodes;
	std::vector<EdgeLine> edges;

	BasicGraph buildBasicGraph();

public:
	Simulation(std::vector<NodeLine>,std::vector<EdgeLine>);
	virtual Graph createInitialConditions(int,int) = 0;

	virtual void perturb(Graph&, int) = 0;
	int peopleAdded();
};

class NaiveSimulation : public Simulation {
public:
	NaiveSimulation(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};

class DisableElevators : public Simulation {
public:
	DisableElevators(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};

class AddGroups : public Simulation {
public:
	AddGroups(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};
class AddWheelchairs : public Simulation {
public:
	AddWheelchairs(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};

class AddDanger : public Simulation {
	int countPolice = 0;
	std::vector<int> dangerNodes;
public:
	AddDanger(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};

class AddBias : public Simulation {
public:
	AddBias(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions(int,int);
	void perturb(Graph&, int);
};
