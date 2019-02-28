#include "CSV/CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

CSVReader::CSVReader(std::string nodeName, std::string edgeName) {
	std::ifstream nodeFile(nodeName);
	nodes.assign(std::istreambuf_iterator<char>(nodeFile), std::istreambuf_iterator<char>());

	std::ifstream edgeFile(edgeName);
	edges.assign(std::istreambuf_iterator<char>(edgeFile), std::istreambuf_iterator<char>());
}

std::pair<std::vector<NodeLine>,std::vector<EdgeLine>> CSVReader::read() {
	std::istringstream nodeStream(nodes);
	std::string line;
	std::vector<NodeLine> nodeVec;
	std::vector<EdgeLine> edgeVec;
	while (std::getline(nodeStream,line)) {
		nodeVec.push_back(readNodeLine(line));
	}

	std::istringstream edgeStream(edges);
	while (std::getline(edgeStream,line)) {
		edgeVec.push_back(readEdgeLine(line));
	}
	return std::make_pair(nodeVec,edgeVec);
}

NodeLine CSVReader::readNodeLine(std::string line) {
	NodeLine nl;
	std::istringstream lineStream(line);
	std::string dump;
	getline(lineStream, dump, ',');
	nl.nodeID = stoi(dump)-1;
	getline(lineStream, dump, ',');
	nl.x = stof(dump);
	getline(lineStream, dump, ',');
	nl.y = stof(dump);
	getline(lineStream, dump, ',');
	nl.z = stof(dump);
	getline(lineStream, dump, ',');
	nl.type = stoi(dump);
	getline(lineStream, dump, ',');
	nl.doorwidth = stof(dump);
	getline(lineStream, dump, ',');
	nl.area = stof(dump);
	return nl;
}

EdgeLine CSVReader::readEdgeLine(std::string line) {
	EdgeLine el;
	std::istringstream lineStream(line);
	std::string dump;
	getline(lineStream, dump, ',');
	el.fromID = stoi(dump)-1;
	getline(lineStream, dump, ',');
	el.toID = stoi(dump)-1;
	return el;
}
