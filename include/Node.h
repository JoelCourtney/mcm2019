#pragma once

#include <vector>
#include "Edge.h"

struct Node {
	double x;
	double y;
	int z;

	std::vector<Edge*> adj;
};
