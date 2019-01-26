#pragma once

#include <vector>
#include "BasicEdge.h"

namespace BasicNodeType {
	enum {
		Exit = 0,
		Escalator = -1,
		Elevator = -2,
		DisabledElevator = -3
	};
}

struct BasicEdge;

struct BasicNode {
	int nodeID;

	float x;
	float y;
	float z;

	int type;

	float area;
	float doorwidth;
	int nrooms;

	std::vector<BasicEdge*> adj;

	BasicNode(int, float, float, float, int, float, float, int);

	void print();
};
