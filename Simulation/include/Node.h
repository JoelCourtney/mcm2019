#pragma once

#include "PersonType.h"
#include "Person.h"
#include "Directions.h"
#include <vector>
#include <tuple>

class Node {
protected:
	float x, y, z;
	int nodeID;

	std::vector<Person*> people;

	Directions directions;

public:
	virtual void update() = 0;
	virtual bool canEnter(int) = 0;
	virtual void enter(Person*) = 0;
};

class Exhibit: Node {
protected:
	int capacity;
	int used;
	std::vector<std::tuple<int,int>> reserved;

	virtual void update();
	virtual bool canEnter(int);
	void enter(Person*);
};

class Exit: Node {
	void update();
	bool canEnter(int);
	void enter(Person*);
};

class Danger: Exhibit {
	void update();
	bool canEnter(int);
};

class Elevator: Node {
	int capacity;
	int used;

	int waitTime;
	bool moving;
	const int waitLimit;

	void update();
	bool canEnter(int);
	void enter(Person*);
};

class Escalator: Node {
	int capacity;
	int used;

	const int waitLimit;
	std::vector<int> waitTimes;
	
	void update();
	bool canEnter(int);
};
