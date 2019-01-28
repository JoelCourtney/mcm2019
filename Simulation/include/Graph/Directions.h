#pragma once

#include <tuple>
#include <vector>
#include "Passage.h"

struct Directions {
	std::vector<Passage> passages;
	int normal = 0;
	int disabled = 0;
	int police = 0;
};
