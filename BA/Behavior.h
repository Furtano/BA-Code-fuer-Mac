#ifndef BEHAVIOR
#define BEHAVIOR

#include "Globals.h"
#include <iostream>
#include <vector>

class Behavior{

public:
	Behavior (int id);
	int antid;
	std::vector <behaviorOfAnt> behaviorLIFO;
};

#endif