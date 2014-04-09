#ifndef GLOBALS
#define GLOBALS

#include "Stats.h"
#include <string>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/opencl.h>
#endif


// ENUMS
	enum statusOfAnt {status_EGG,status_GRUB, status_PUPPET, status_IMAGO, status_ANT};
	enum behaviorOfAnt {randommm, nest, slide, food, fight};

// MODES
	// If True, it executes the google tests
	#define TEST_MODE false
	// Activates faster Ant Simulation
	#define BOOST false

// GRAPGICS
	#define WINDOW_WIDTH 1100
	#define WINDOW_HEIGHT 800
	#define SIZEOFANANT 2
	#define FPS 30

	#define WIDTH 800
	#define HEIGHT 800
// SIM GLOBALS
	// ARRAY_SIZE must be >= startPopulation !!!
	#define ARRAY_SIZE 200000
	#define startPopulation 200000
	#define MAXFOOD 1
#define NEST_CLEAN_AREA 15
	// How much Food
    #define FOOD_FACTOR 1
	#define STARTPOSX 400
	#define STARTPOSY 400
	#define ENDEPOSX 300
	#define ENDEPOSY 200
	#define ANT_VIEWRADIUS 3
	#define PHERMON_SEARCH_RADIUS 45
	
	#define MAXFOODforBreed 3
	// DAYS e.g. AN EGG NEEDS TO DEVELOP
	#define endDateEgg 14
	#define endDateGrub 10
	#define endDatePuppet 5
	#define endDateImago 5

	#define MAX_ENEMIES 10

#endif
