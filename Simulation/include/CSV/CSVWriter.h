#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class CSVWriter {
	std::ofstream outFile;

public:
	CSVWriter(std::string);

	void nextLine(std::vector<int>);

	void commit();
};
