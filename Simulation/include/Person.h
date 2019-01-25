#pragma once

#include "Directions.h"
#include "PersonType.h"

class Person {
	static const int type = PersonType::Undefined;

public:
	virtual bool move(Directions*);
};

class Tourist: Person {
	int groupID;
	static const int type = PersonType::Normal;

	bool move(Directions*);
};

class DisabledTourist: Tourist {
	static const int type = PersonType::Disabled;

	bool move(Directions*);
};

class Police: Person {
	static const int type = PersonType::Police;

	bool move(Directions*);
};
