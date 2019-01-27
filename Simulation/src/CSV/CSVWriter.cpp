#include "CSV/CSVWriter.h"
#include <iostream>

CSVWriter::CSVWriter(std::string fileName) {
	outFile.open(fileName);
}

void CSVWriter::nextLine(std::vector<int> data) {
	for (int i = 0; i < data.size() - 1; i++) {
		outFile << std::to_string(data.at(i)) << ",";
	}
	outFile << std::to_string(data.back()) << "\n";
}

void CSVWriter::commit() {
	outFile.close();
}
