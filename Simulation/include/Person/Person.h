#pragma once

#include "PersonType.h"

class Directions;

class Person {
public:
	virtual ~Person();

	static const int type = PersonType::Undefined;

	virtual bool move(Directions*) = 0;
};

class Tourist: public Person {
protected:
	int groupID;

public:
	Tourist(int);
	~Tourist();

private:
	static const int type = PersonType::Normal;

	bool move(Directions*);
};

class DisabledTourist: public Tourist {
	static const int type = PersonType::Disabled;

public:
	DisabledTourist(int);

private:
	bool move(Directions*);
};

class Police: Person {
	static const int type = PersonType::Police;

	bool move(Directions*);
};
