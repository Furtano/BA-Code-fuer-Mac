

int getPheromonMapID (int x, int y){
	int WIDTH = 800;

	return y*WIDTH+x;
}

// Checks if Ant has Smelled a Pheromon
// if yes, it gets into Pheromon Mode

// TODO: SPEED INTEGRATION !!!
__kernel void pheromon (
	__global  float *trash1,
	__global  float *trash2,
	__global  int *pheromonMap,
	__global  float *antX,
	__global  float *antY,
	__global  int * modus,
	__global  bool * isCarryingFood
	)
{
	int i = get_global_id(0);

	if (isCarryingFood[i] == false){

		// OutOfIndex Check
		if (
			(antX[i] > 1 && antX[i] < 799)
			&& 
			(antY[i] > 1 && antY[i] < 799)
			){

				int pheromonID = getPheromonMapID(antX[i]-1, antY[i]-1);
				int pheromonID2 = getPheromonMapID(antX[i], antY[i]-1);
				int pheromonID3 = getPheromonMapID(antX[i]+1, antY[i]-1);
				int pheromonID4 = getPheromonMapID(antX[i]-1, antY[i]);
				int pheromonID5 = getPheromonMapID(antX[i]+1, antY[i]);
				int pheromonID6 = getPheromonMapID(antX[i]-1,antY[i]+1);
				int pheromonID7 = getPheromonMapID(antX[i], antY[i]+1);
				int pheromonID8 = getPheromonMapID(antX[i]+1, antY[i]+1);
				if (pheromonMap[pheromonID] > 0
					|| pheromonMap[pheromonID2] > 0
					|| pheromonMap[pheromonID3] > 0
					|| pheromonMap[pheromonID4] > 0
					|| pheromonMap[pheromonID5] > 0
					|| pheromonMap[pheromonID6] > 0
					|| pheromonMap[pheromonID7] > 0
					|| pheromonMap[pheromonID8] > 0

					){
						modus[i] = 3;
				}
		}



	}



}