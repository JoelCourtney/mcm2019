#pragma once

#include <vector>
#include "BasicNode.h"

struct BasicNode;

namespace EdgeType {
	enum {
		Normal,
		NoWheelChair,
		OnlyWheelChair,
		Dangerous,
	};
}

struct BasicEdge {
	int c; // capacity of each pseudo node
	int w; // width of doorways
	int n; // number of pseudo nodes on edge

	int type;

	BasicNode* from;
	BasicNode* to;

	BasicEdge(int, int, int, int, BasicNode*, BasicNode*);
};
