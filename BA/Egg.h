#ifndef EGG
#define EGG

#include "Breed.h"
#include "Globals.h"
class Egg : public Breed {

public:

	Egg (int dayss){
		status = status_EGG;
		days = dayss;
		endDate = endDateEgg;
		food = 10;
		lifeStatus = 0;
	}
	//this.status = status_PUPPET;
	
	void dayIsOver(){
		// Egg doesnt need food
		this->food -= 0;
	}
};

#endif