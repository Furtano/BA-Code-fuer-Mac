/*
*
* This is the OpenCL Kernel. It calculates each step for each ant.
*
*/

float lenghtOfVector (float x, float y){

	 return native_sqrt(pown(x,2) + pown(y,2));
}
int getPheromonMapID (int x, int y){
	int WIDTH = 800;

	return y*WIDTH+x;
}

/***
	in: newAntX, newAntY
	out:  newAntX, newAntY
**/
__kernel void stepSizeAnt(
	__global  float *antX,
	__global  float *antY,
	__global  float *newAntX,
	__global  float *newAntY,
	__global  int *targetX,
	__global  int *targetY,
	__global  float *resultX,
	__global  float *resultY,
	__global  int *lifeStadium, 
	__global  int *speed,
	__global  int *mode,
	__global int *pheromonMap
	
	)
{
	int gid = get_global_id(0);


	
		// only if Ant is living
		if (lifeStadium[gid] == 1){



			/**

			IF ANT GETS AN NEW TARGET, GO TO IT 
			WHILE SNIFFING

			**/
			// if Ant is not in PheromonMode
			if (mode[gid] != 3){
				// Neuen Richtungsvektor berechnen (in Welche Richtung soll die Ameise laufen)
				resultX[gid] = (targetX[gid]-newAntX[gid]);
				resultY[gid] = (targetY[gid]-newAntY[gid]);

				// Normvektor ausrechnen normalisieren



				float norm = lenghtOfVector(resultX[gid], resultY[gid]);

				// Richtungsvektor normalisieren
				resultX[gid] = (resultX[gid] / norm);
				resultY[gid] = (resultY[gid] / norm);

				// Ameisenschritt machen
				// neue Ameisenposition = Alte Position + (neue Schrittposition * Geschwindigkeit)
				newAntX[gid] +=   (resultX[gid])*speed[gid];
				newAntY[gid] +=   (resultY[gid])*speed[gid];

			}



			/**

			IF ANT SNIFFS
			FOLLOW THE PHEROMONS

			**/


				if(mode[gid] == 3) {

				// Temp X,Y 
				int x = newAntX[gid];
				int y = newAntY[gid];

				// RANDOM SEED
				int strongID = getPheromonMapID(newAntX[gid],newAntY[gid]);
				int strongestValue = pheromonMap[strongID];

				// FOR RADIUS XXX
				//            X X
				//            XXX
				int radius = 10;
				for (int i = newAntY[gid]-radius-speed[gid]; i < newAntY[gid]+radius+speed[gid]; i++){
					for (int j = newAntX[gid]-radius-speed[gid]; j < newAntX[gid]+radius+speed[gid]; j++){

						if (i > 0 && j > 0 && i < 800 && j < 800){
							// check 1 Radius Field
							int id = getPheromonMapID(j,i);
							int checkFieldValue = pheromonMap[id];


							// found new Direction???
							if (checkFieldValue > strongestValue){
								// set new Highest
								strongestValue = checkFieldValue;
								x = j;
								y = i;
							}

						}

					}

				}

				newAntX[gid] =  x ;
				newAntY[gid] =  y ;

			}




	}
	
}