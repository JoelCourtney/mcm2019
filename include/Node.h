#pragma once

#include <vector>
#include "Edge.h"

struct Edge;

struct Node {
	double x;
	double y;
	int z;

	std::vector<Edge*> adj;

	Node(double, double, int);
};
