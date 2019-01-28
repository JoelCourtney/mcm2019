#include <iostream>
#include "BasicGraph/BasicGraph.h"
#include <iostream>
#include "Graph/Graph.h"
#include "CSV/CSVReader.h"
#include "CSV/CSVWriter.h"
#include "Simulation/Simulation.h"
#include <time.h>
#include <stdlib.h>
#include "Constants.h"

int target_people = 9000;
int stairWait = 1;

int simulate(Simulation* sim) {
	std::cout << "Constructing graph..." << std::endl;
	std::cout << "Wait time is " << stairWait << std::endl;
	Graph g = sim->createInitialConditions(target_people, stairWait);
	std::cout << "Simulating...";
	int tick;
	for (tick = 0; tick < 1500000 && g.getExited() < sim->peopleAdded(); tick++) {
		sim->perturb(g, tick);
		//writer.nextLine(g.update());
		g.update();
		if (tick % 500 == 0) {
			//g.printExits();
			std::cout << ".";
			std::cout.flush();
		}
	}
	std::cout << std::endl;
	//writer.commit();
	g.printExits();
	std::cout << "Simulation took " << tick << " ticks to run.\n\n";
	return tick;
}

int main() {
	srand(time(NULL));

	std::vector<int> times;
	
	CSVReader reader("../Rendering/exports/MasterNodes.csv","../Rendering/exports/MasterEdges.csv");
	CSVWriter writer("../Rendering/imports/NaiveSetup.csv");
	std::cout << std::endl;
	auto raw = reader.read();
	Simulation* sim = new AddDanger(raw.first, raw.second);
	for (stairWait = 1; stairWait < 60; stairWait++) {
		for (int i = 0; i < 3; i++)
			times.push_back(simulate(sim));
	}
	delete sim;
	std::cout << std::endl << "Runtime list:\n" << times.front();
	for (int i = 1; i < times.size(); i++) {
		std::cout << "\n" << times.at(i);
	}
	std::cout << std::endl;
}
