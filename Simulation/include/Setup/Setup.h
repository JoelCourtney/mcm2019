#pragma once

#include <random>
#include <iostream>
#include "Graph/Graph.h"
#include "BasicGraph/BasicGraph.h"
#include "CSV/Lines.h"

class Setup {
protected:
	int people;
	std::vector<NodeLine> nodes;
	std::vector<EdgeLine> edges;

	BasicGraph buildBasicGraph();

public:
	Setup(std::vector<NodeLine>,std::vector<EdgeLine>);
	virtual Graph createInitialConditions() = 0;

	int peopleAdded();
};

class NaiveSetup : public Setup {
public:
	NaiveSetup(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions();
};

class DisableElevators : public Setup {
public:
	DisableElevators(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions();
};

class AddGroups : public Setup {
public:
	AddGroups(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions();
};

class AddWheelchairs : public Setup {
public:
	AddWheelchairs(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions();
};

class AddDanger : public Setup {
public:
	AddDanger(std::vector<NodeLine>,std::vector<EdgeLine>);
	Graph createInitialConditions();
};
