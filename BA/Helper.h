#ifndef HELPER_H
#define HELPER_H

#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Globals.h"
#include "clInitFunctions.hpp"
#include "Food.h"


class Helper {
public:
	std::vector <int*> selectedAnts;
	bool viewRadiusMode;
	bool targetMode;
	bool gridMode;
	bool selectionMode;
	bool pheromonMode;
	bool pauseSimulation;

	Helper();

	static int getRandomInt(int high, int low );
	static long filesize(const char *filename);
	static float getLenghtOfVector(float x, float y);
	void checkInput(openCLinit *init, Stats* stats, sf::RenderWindow *window, std::vector <Food*> *food);
	static void initTestPheromon(openCLinit *init);
};

#endif
