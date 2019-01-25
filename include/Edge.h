#pragma once

#include <vector>
#include "Node.h"

struct Node;

namespace EdgeType {
	enum {
		Normal,
		NoWheelChair,
		OnlyWheelChair,
		Dangerous,
	};
}

struct Edge {
	int c; // capacity of each pseudo node
	int w; // width of doorways
	int n; // number of pseudo nodes on edge

	int type;

	Node* from;
	Node* to;

	Edge(int, int, int, int, Node*, Node*);
};
