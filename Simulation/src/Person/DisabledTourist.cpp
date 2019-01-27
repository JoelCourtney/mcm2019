#include "Person/Person.h"
#include "Graph/Directions.h"

DisabledTourist::DisabledTourist(int ID): Tourist(ID) {}

bool DisabledTourist::move(Directions* dir) {
	return dir->passages.at(dir->disabled).moveIfPossible(groupID, static_cast<Person*>(this));
}
