#pragma once

#include <tuple>
#include "Node.h"
#include "Door.h"
#include "Passage.h"

class Node;

class Directions {
	Passage normal;
	Passage wheelchair;
	Passage police;
};
