#pragma once

struct NodeLine {
	int nodeID;
	float x;
	float y;
	float z;
	int type;
	float area;
	float doorwidth;
};
struct EdgeLine {
	int fromID;
	int toID;
};
