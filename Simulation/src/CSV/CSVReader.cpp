#include "CSV/CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

CSVReader::CSVReader(std::string nodeName, std::string edgeName) {
	std::ifstream nodeFile(nodeName);
	nodes.assign(std::istreambuf_iterator<char>(nodeFile), std::istreambuf_iterator<char>());

	std::ifstream edgeFile(edgeName);
	edges.assign(std::istreambuf_iterator<char>(edgeFile), std::istreambuf_iterator<char>());
}

BasicGraph CSVReader::buildBasicGraph() {
	BasicGraph g;
	std::istringstream nodeStream(nodes);
	std::string line;
	while (std::getline(nodeStream,line)) {
		NodeLine nodeLine = readNodeLine(line);
		BasicNode n(
			nodeLine.nodeID,
			nodeLine.x,
			nodeLine.y,
			nodeLine.z,
			nodeLine.type,
			nodeLine.area,
			nodeLine.doorwidth
		);
		g.addNode(n);
	}

	std::istringstream edgeStream(edges);
	while (std::getline(edgeStream,line)) {
		EdgeLine edgeLine = readEdgeLine(line);
		BasicEdge e(
			edgeLine.fromID,
			edgeLine.toID
		);
		g.addEdge(e);
	}
	return g;
}

CSVReader::NodeLine CSVReader::readNodeLine(std::string line) {
	NodeLine nl;
	std::istringstream lineStream(line);
	std::string dump;
	getline(lineStream, dump, ',');
	nl.nodeID = stoi(dump);
	getline(lineStream, dump, ',');
	nl.x = stof(dump);
	getline(lineStream, dump, ',');
	std::cout << "read " << dump << std::endl;
	nl.y = stof(dump);
	std::cout << "pasted " << nl.y << std::endl;
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

CSVReader::EdgeLine CSVReader::readEdgeLine(std::string line) {
	EdgeLine el;
	std::istringstream lineStream(line);
	std::string dump;
	getline(lineStream, dump, ',');
	el.fromID = stoi(dump);
	getline(lineStream, dump, ',');
	el.toID = stoi(dump);
	return el;
}
