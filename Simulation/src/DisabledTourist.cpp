#include "Person.h"
#include "Directions.h"

bool DisabledTourist::move(Directions* dir) {
	return dir->wheelchair.moveIfPossible(groupID, static_cast<Person*>(this));
}
