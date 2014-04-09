#ifndef PUPPET
#define PUPPET

#include "Breed.h"
#include "Globals.h"
class Puppet : public Breed {

public:

	Puppet (int dayss){
		status = status_PUPPET;
		days = dayss;
		endDate = endDatePuppet;
		food = 5;
		lifeStatus = 0;
	}
	//this.status = status_PUPPET;
	
	void dayIsOver(){
		// Puppet doesnt need food
		this->food -= 0;
	}
};

#endif