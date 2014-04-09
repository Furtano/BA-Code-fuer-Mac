#ifndef ENEMY
#define ENEMY

#include "Area.h"
#include "clInitFunctions.hpp"
#include "Helper.h"
#include "Stats.h"

class Enemy : public Area {

	public: 
		openCLinit * init;
		int attackRadius;
		int attackTime;
		bool ableToAttack;
		Stats *stats;
		Stats statsFromEating;
		Enemy (openCLinit * init, int x, int y, int attackRadius, int attackTime, Stats *stats);
		void checkIfAttackIsPossible(int i);
		void eat();
		void check();

};

#endif