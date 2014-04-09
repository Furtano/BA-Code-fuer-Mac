#include "Enemy.h"

Enemy::Enemy (openCLinit * init, int x, int y, int attackRadius, int attackTime, Stats *stats){
	this->init = init;
	this->x = x;
	this->y = y;
	this->attackRadius = attackRadius;
	this->attackTime = attackTime;
	this->stats = stats;
	this->ableToAttack = true;
}

void Enemy::checkIfAttackIsPossible(int i){

	// find all Ants in Range of Enemy
	if (ableToAttack){
		
		if (init->lifeStadium[i] == 1){

			// calc length of Vector
			int xComponent = x - init->antX[i];
			int yComponent = y - init->antY[i];

			float range = abs(Helper::getLenghtOfVector(xComponent,yComponent));

			//std::cout << "\n" << range;

			// Ant is in Attack Range of Enemy
			if (range < attackRadius){

				// Ant is Dead
				init->lifeStadium[i] = 0;
				stats->killedAnts++;
				std::cout << "KILLED ANT" << i ;
				// eat the killed Ant (time will elapse and Enemy cant attack other Ants!)
				eat();
			}
		}
	}
	// Check if Enemy is ready with eating
	else {
		check();
	}

}

void Enemy::eat(){
	statsFromEating.days = stats->days;
	this->ableToAttack = false;
}

void Enemy::check(){
	// Verdaut =)
	if (statsFromEating.days + this->attackTime == stats->days){
		this->ableToAttack = true;
	}
}