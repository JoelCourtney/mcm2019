#include "Person/Person.h"
#include <iostream>

Person::~Person() {
	std::cout << "top delete\n";
}
