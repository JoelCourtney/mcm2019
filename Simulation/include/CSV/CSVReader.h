#pragma once

#include <string>
#include "BasicGraph/BasicGraph.h"

class CSVReader {
	std::string nodes;
	std::string edges;

	struct NodeLine {
		int nodeID;
		float x;
		float y;
		float z;
		int type;
		float area;
		float doorwidth;
		int nrooms;
	};
	struct EdgeLine {
		int fromID;
		int toID;
	};

public:
	CSVReader(std::string,std::string);

	BasicGraph buildBasicGraph();

private:
	NodeLine readNodeLine(std::string);
	EdgeLine readEdgeLine(std::string);
};
