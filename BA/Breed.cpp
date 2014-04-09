#include "Breed.h"
#include "Globals.h"

Breed::Breed(){
	this->aviableFood = 30;
}
void Breed::feed (int food) {

	// feed
	this->food += food;

	// Ant has enought food
	if (this->food > MAXFOODforBreed){
		this->food = MAXFOODforBreed;
	}
}

