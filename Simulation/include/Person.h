#pragma once

#include "PersonType.h"

class Directions;

class Person {
	static const int type = PersonType::Undefined;

public:
	virtual bool move(Directions*) = 0;
};

class Tourist: public Person {
protected:
	int groupID;

private:
	static const int type = PersonType::Normal;

	bool move(Directions*);
};

class DisabledTourist: public Tourist {
	static const int type = PersonType::Disabled;

	bool move(Directions*);
};

class Police: Person {
	static const int type = PersonType::Police;

	bool move(Directions*);
};
