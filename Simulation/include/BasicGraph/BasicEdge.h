#pragma once

#include <vector>
#include "BasicNode.h"

struct BasicNode;

//namespace BasicEdgeType {
	//enum {
		//Normal,
		//NoWheelChair,
		//OnlyWheelChair,
		//Dangerous,
	//};
//}

struct BasicEdge {
	BasicNode* from;
	BasicNode* to;

	BasicEdge(BasicNode*, BasicNode*);

	void print();
};
