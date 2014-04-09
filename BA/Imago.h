#ifndef IMAGO
#define IMAGO

#include "Breed.h"
#include "Globals.h"
class Imago : public Breed {

public:

	Imago (int dayss){
		status = status_IMAGO;
		days = dayss;
		endDate = endDateImago;
		food = 5;
		lifeStatus = 0;
	}
	//this.status = status_PUPPET;
	
	void dayIsOver(){
		this->food -= 2;
	}
};

#endif