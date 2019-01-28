#include <iostream>
#include "BasicGraph/BasicGraph.h"
#include <iostream>
#include "Graph/Graph.h"
#include "CSV/CSVReader.h"
#include "CSV/CSVWriter.h"
#include "Setup/Setup.h"
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(NULL));
	
	CSVReader reader("../Rendering/exports/MasterNodes.csv","../Rendering/exports/MasterEdges.csv");
	CSVWriter writer("../Rendering/imports/NaiveSetup.csv");
	auto raw = reader.read();
	AddWheelchairs setup(raw.first, raw.second);
	Graph g = setup.createInitialConditions();
	int tick;
	for (tick = 0; tick < 15000 && g.getExited() < setup.peopleAdded(); tick++) {
		writer.nextLine(g.update());
		if (tick % 1000 == 0) {
			g.printExits();
			std::cout << std::endl;
		}
	}
	writer.commit();
	g.printExits();

	std::cout << "Simulation took " << tick << " ticks to run.\n";
};
