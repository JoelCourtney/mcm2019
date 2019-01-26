#include "Person/Person.h"
#include "Graph/Directions.h"

bool Police::move(Directions* dir) {
	return dir->police.moveIfPossible(-1, this);
}
