#pragma once

#include <tuple>
#include <vector>
#include "Passage.h"

struct Directions {
	std::vector<Passage> passages;
	int normal;
	int disabled;
	int police;
};
