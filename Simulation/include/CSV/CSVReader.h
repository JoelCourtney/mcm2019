#pragma once

#include <string>
#include "BasicGraph/BasicGraph.h"
#include "CSV/Lines.h"

class CSVReader {
	std::string nodes;
	std::string edges;


public:
	CSVReader(std::string,std::string);

	std::pair<std::vector<NodeLine>,std::vector<EdgeLine>> read();

private:
	NodeLine readNodeLine(std::string);
	EdgeLine readEdgeLine(std::string);
};
