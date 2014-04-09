#ifndef SIMULATION
#define SIMULATION

#include "Globals.h"
#include "Helper.h"
#include "clInitFunctions.hpp"
#include "Breed.h"
#include "Egg.h"
#include "Puppet.h"
#include "Grub.h"
#include "Imago.h"
#include "Food.h"
#include "Enemy.h"
#include <iostream>

class Simulation {
public:
	std::vector <Breed*> breed;
	std::vector <Food*> food;
	std::vector <Enemy*> enemy;
	

	void makeStats(Stats * stats, openCLinit *init);
	//void antQueen(sf::Clock * timeSimulationRuned, openCLinit *init, Stats * stats);
	void checkBreed(Stats * stats);
	void fillMapWithFood(openCLinit *init);
	void fillMapWithFood2(openCLinit *init);
	void simulate(openCLinit * init, Stats* stats);
	void checkIfAntFoundFood (int antid, openCLinit *init);
	void checkIfAntFoundFood2 (int antid, openCLinit *init, Stats* stats);
	void elapsePheromons(openCLinit * init);
	void deleteNestFromPheromons (openCLinit * init);
	void getNewTarget(openCLinit *init, int i);
	void fillMapWithEnemies(openCLinit *init, Stats * stats);
};

#endif
