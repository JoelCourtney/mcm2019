#include "Person.h"
#include "Directions.h"

bool Tourist::move(Directions* dir) {
	return dir->normal.moveIfPossible(groupID, this);
}
