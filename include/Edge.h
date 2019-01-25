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
	int w;

	Node* from;
	Node* to;

	int type;
};
