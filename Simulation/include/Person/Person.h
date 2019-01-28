#pragma once

#include "PersonType.h"
#include <vector>

class Directions;
class Node;

class Person {
public:
	virtual ~Person();

	virtual bool move(Directions*) = 0;
	virtual int getType() = 0;
};

class Tourist: public Person {
protected:
	int groupID;

public:
	Tourist(int);
	~Tourist();

private:
	bool move(Directions*);
	int getType();
};

class DisabledTourist: public Tourist {
	std::vector<Node*> previous;

public:
	DisabledTourist(int);
	int getType();

private:
	bool move(Directions*);
};

class Police: public Person {
	public:
	bool move(Directions*);
	int getType();
};
