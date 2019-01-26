#pragma once

#include <vector>
#include "BasicEdge.h"

struct BasicEdge;

struct BasicNode {
	double x;
	double y;
	int z;

	std::vector<BasicEdge*> adj;

	BasicNode(double, double, int);
};
