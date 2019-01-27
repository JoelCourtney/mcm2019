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
	int fromID;
	int toID;

	float distance;

	BasicEdge(int,int);

	void print();
};
