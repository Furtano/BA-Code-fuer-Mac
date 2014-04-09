#ifndef GRUB
#define GRUB

#include "Breed.h"
#include "Globals.h"
class Grub : public Breed {

public:

	Grub (int dayss){
		status = status_GRUB;
		days = dayss;
		endDate = endDateGrub;
		food = 2;
		lifeStatus = 0;
	}

	
	void dayIsOver(){
		this->food -= 3;
	}
	//this.status = status_PUPPET;

};

#endif