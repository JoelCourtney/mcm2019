#pragma once

#include "Person/PersonType.h"
#include "Graph/Directions.h"
#include <vector>
#include <tuple>

class Person;

class Node {
protected:
	int nodeID;


public:
	Directions directions;


	std::vector<Person*> people;
	Node(int);

	virtual int update() = 0;
	virtual bool canEnter(int) = 0;
	virtual void enter(Person*) = 0;

	void addPassage(Passage);
	void changePreference(int);

	virtual void print();
	virtual void printExit() {};
	virtual int getExited() {return 0;}
	int getID();
};

class Exhibit: public Node {

protected:
	std::vector<Exhibit*> exhibits;
	int capacity;
	int used = 0;

public:
	virtual int getNumberOfPeople() {return used;}
	Exhibit(int,int);

	virtual int update();
	virtual bool canEnter(int);
	void enter(Person*);

	void addRoom(Exhibit*);

	virtual void print();

	virtual bool isDangerous();
};

class Room: public Exhibit {
public:
	Room(int,int);
	int getNumberOfPeople();
	void print();

	bool isDangerous();
};

class Danger: public Exhibit {
	int exited = 0;
public:
	Danger(int,int);
	int getNumberOfPeople();
	void print();

	bool canEnter(int);

	int update();

	bool isDangerous();

	int getExited();
};

class Exit: public Node {
	int used = 0;

public:
	Exit(int);

	int update();
	bool canEnter(int);
	void enter(Person*);

	void print();
	void printExit();
	int getExited();
};

class Elevator: public Node {
	int capacity;
	int used = 0;

	int waitTime;
	bool moving = false;
	const int waitLimit;

public:
	Elevator(int,int,int);

	int update();
	bool canEnter(int);
	void enter(Person*);

	void print();
};

class Escalator: public Node {
	int capacity;
	int used = 0;

	const int waitLimit;
	std::vector<int> waitTimes;

public:
	Escalator(int,int,int);
	
	int update();
	bool canEnter(int);
	void enter(Person*);

	void print();
};

