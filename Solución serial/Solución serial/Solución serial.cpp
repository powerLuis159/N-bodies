// Solución serial.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"


int main()
{
	/* seudocigo
	1 get input data;
	2 for each timestep{
	3	if(timestep output) Print position and velocities of particles;
	4	for each particle q
	5		compute total force on q;
	6	for each particle q
	7		Compute position and velocity of q;
	8 }
	9 Print position and velocities of the particles;*/


	const int X = 0, Y = 1;
	int pos[10][2], forces[10][2];
	/*lineas 4 y 5
	for each particle q{
		for each particle k!=q{
			x_diff= pos[q][X]-pos[k][X];
			y_diff=pos[q][Y]-pos[k][Y];
			dist= sqrt(x_diff*x_diff+y_diff*y_diff);
			dist_cubed=dist*dist*dist;
			forces[q][X]-=G*masses[q]*masses[k]/dist_cubed*x_diff;
			forces[q][Y]-=G*masses[q]*masses[k]/dist_cubed*y_diff;
		}
	}*/

	/*lineas 6 y 7
	pos[q][X]+=delta_t*vel[q][X];
	pos[q][Y]+=delta_t*vel[q][Y];
	vel[q][X]+=delta_t/masses[q][X]*forces[q][X];
	vel[q][Y]+=delta_t/masses[q][X]*forces[q][X];
	*/

    return 0;
}

