#pragma once

#include "Person/PersonType.h"
#include "Graph/Directions.h"
#include <vector>
#include <tuple>

class Person;

class Node {
protected:
	int nodeID;
	float x, y, z;

	std::vector<Person*> people;

	Directions directions;

public:
	Node(int,float,float,float);

	virtual void update() = 0;
	virtual bool canEnter(int) = 0;
	virtual void enter(Person*) = 0;

	void setDirections(Directions);

	virtual void print();
};

class Exhibit: public Node {
protected:
	int capacity;
	int used;
	std::vector<std::tuple<int,int>> reserved;

public:
	Exhibit(int,float,float,float,int);

	virtual void update();
	virtual bool canEnter(int);
	void enter(Person*);

	void print();
};

class Exit: public Node {
	int used;

public:
	Exit(int,float,float,float);

	void update();
	bool canEnter(int);
	void enter(Person*);

	void print();
};

class Danger: Exhibit {
	void update();
	bool canEnter(int);
	
};

class Elevator: public Node {
	int capacity;
	int used;

	int waitTime;
	bool moving = false;
	const int waitLimit;

public:
	Elevator(int,float,float,float,int,int);

	void update();
	bool canEnter(int);
	void enter(Person*);

	void print();
};

class Escalator: public Node {
	int capacity;
	int used;

	const int waitLimit;
	std::vector<int> waitTimes;

public:
	Escalator(int,float,float,float,int,int);
	
	void update();
	bool canEnter(int);
	void enter(Person*);

	void print();
};

