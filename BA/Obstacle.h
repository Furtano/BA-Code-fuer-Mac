#ifndef OBSTACLE
#define OBSTACLE
#include "Area.h"

class Obstacle : public Area {

public:

	int width;
	int height;
	Obstacle (int x, int y, int width, int height);



};

#endif