#ifndef BREED
#define BREED
#include "Globals.h"

class Breed {

public:		
	Breed();
	statusOfAnt status;
	int days;
	int endDate;
	int food;
	// 0 == Dead, 1 == Alive 
	bool lifeStatus;
	int aviableFood;

	/** Gibt der Brut Futter
	*  @param[in,out] food die Anzahl von Futter
	*  @return Die Summe der beiden Zahlen a und b.  
	*  @see Addiere(double,double)  
	*/
	void feed(int food);
	void dayIsOver();

};

#endif