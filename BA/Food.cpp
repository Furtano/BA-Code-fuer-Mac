#include "Food.h"


/**********************************************************************************************//**
 * @fn	Food::Food (int x, int y, int volume)
 *
 * @brief	Constructor.
 *
 * @author	Blnsc 000
 * @date	18.03.2014
 *
 * @param	x	  	The x coordinate.
 * @param	y	  	The y coordinate.
 * @param	volume	The volume.
 **************************************************************************************************/

Food::Food (int x, int y, int volume){
	this->x = x;
	this->y = y;
	this->volume = volume;

}