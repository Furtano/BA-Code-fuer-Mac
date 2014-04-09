//#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <thread>
#include <vector>
//#include <array>
#include <iomanip>
//#include <thread>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "clInitFunctions.hpp"


#include "Egg.h"
#include "Puppet.h"
#include "Grub.h"
#include "Imago.h"

#include "Helper.h"
#include "Simulation.h"
#include "Drawer.h"
#include "Behavior.h"
#include "Obstacle.h"



openCLinit *init = new openCLinit;
Drawer *drawer = new Drawer;
Helper helper;
Stats *stats = new Stats;
Simulation *sim = new Simulation;


/**
MODES
**/

bool targetMode = false;
bool gridMode = false;
bool viewRadiusMode = false;


int selectorWidth = 1;
int selectorHeight = 1;






// IDs of Ants which are Selected are saved in the Vector


///
//  Constants
//
sf::Clock timeSimulationRuned;





void initVariables (){
	// Random Seed
	

	


	//Helper::initTestPheromon(init);
	stats->breed = 0;
	stats->eggs = 0;
	stats->grubs = 0;
	stats->puppets = 0;
	stats->imagos = 0;
	stats->livingAnts = startPopulation;
	stats->days = 0;
	stats->months = 0;
	stats->years = 0;
	stats->stats_number_of_living_ants = 0;
	stats->foodCatchingAnts =0;
	stats->pheromonSearching = 0;
	stats->earnedFood = 0;
	stats->killedAnts = 0;
	stats->fps = 0;
	//antsBehavior.push_back(new Behavior(i));


	if (BOOST)
		sim->fillMapWithFood(init);
	else
		sim->fillMapWithFood2(init);

	sim->fillMapWithEnemies(init, stats);


	for (int i = 0; i < ARRAY_SIZE; i++){
		int randomm = 0;

		do {
			randomm =  Helper::getRandomInt(WIDTH, 0);
		}
		while (init->targetX[i] == randomm);

		init->targetX[i] = randomm;

		do {
			randomm = Helper::getRandomInt(WIDTH, 0);
		}
		while (init->targetY[i] == randomm);

		init->targetY[i] = randomm;
	}

	// TEST PHEROMON MAP
	//for (int i = 0; i < 800; i++){
	//	//init->pheromonMap[i*WIDTH+i] = i; 
	//	init->pheromonMap[300*WIDTH+i] = i; 

	//}
}




void antQueen(){
	float tempdays;
	float oldTempDays = 0;



		tempdays = timeSimulationRuned.getElapsedTime().asSeconds();
		tempdays = (float)((int)(tempdays*100))/100;
		// 1 new day:
		if (fmod(tempdays, 1) == 0 ){	
			sim->makeStats(stats,init);
			// !first round
			if (oldTempDays != tempdays){

				// A new Ant Spawns in The Game ;)
				if (startPopulation >ARRAY_SIZE)
					init->lifeStadium[stats->livingAnts] = 1;

				// Queen spawns an Egg 
				if (stats->days % 3 == 0 && stats->days != 0){
					int random = Helper::getRandomInt(10,1);
					for (int z = 0; z < random; z++)
						sim->breed.push_back(new Egg(0));
				}

				// For Stats
				sim->checkBreed(stats);
				// 1 Day is Over
				stats->days++;
				//sim->elapsePheromons(init);

				for (Breed *ant : sim->breed){
					ant->days++;
				}



				if (stats->days % 30 == 0 && stats->days != 0){
					stats->days = 0;
					stats->months++;
				}

				if (stats->months % 12 == 0 && stats->months != 0){
					stats->months = 0;
					stats->years++;
				}

			}
			// For Twice-Failure Checking
			oldTempDays = tempdays;
		}


        

}




int main(int argc, char** argv)
{


	srand( static_cast<unsigned int>(time(NULL)));



	//if (TEST_MODE){
	//	::testing::InitGoogleTest(&argc, argv);
	//	return RUN_ALL_TESTS();
	//}

	if (!TEST_MODE) {
		
		initVariables();
		
	
		//std::thread statisticsThread (antQueen);
		 sf::Clock clock;
		 float lastTime = 0;

		// SFML Graphics Loop + Simulation Loop
		while (drawer->window->isOpen())
		{
            antQueen();
			float currentTime = clock.restart().asSeconds();
            stats->fps = 1.f / currentTime;
            lastTime = currentTime;

		
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (drawer->window->pollEvent(event))
			{

				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					drawer->window->close();
				
			}

			if (!helper.pauseSimulation){
				// 1. make GPU simlation Checks
				init->startOpenCLmain();

				// 2. make CPU simlation Checks
				sim->simulate(init, stats);
			}
			// 3. check the Keyboard input from user
			helper.checkInput(init, stats, drawer->window, &sim->food);

			// 4. draw the Simulation 
			drawer->drawSimulation(init, &helper, sim, stats);

		// ENDE OF SIMULATION
		}
		

		// Cleanup
		//statisticsThread.join();
		init->CleanupEnd();
		
		delete init;
		delete drawer;
		delete stats;
		delete sim;
		


		// :) 
		return 0;

	}
}
