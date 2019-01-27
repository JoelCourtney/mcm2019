#pragma once

#include <random>
#include <iostream>
#include "Graph/Graph.h"
#include "BasicGraph/BasicGraph.h"

class Setup {
protected:
	int people;
	BasicGraph bg;
public:
	Setup(BasicGraph);
	virtual Graph createInitialConditions() = 0;

	int peopleAdded();
};

class NaiveSetup : public Setup {
public:
	NaiveSetup(BasicGraph);
	Graph createInitialConditions();
};
