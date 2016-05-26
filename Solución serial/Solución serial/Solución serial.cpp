// Solución serial.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <math.h>

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

	//numero de particulas: 400
	//numero de timesteps: 1000
	
	const int X = 0, Y = 1, particulas=400, timestep=1000;
	const double G = 0.000000000663, delta=0.01;
	double pos[particulas][2], forces[particulas][2], forces_qk[2], masses[particulas], vel[particulas][2];
	for (int i = 0; i < particulas; i++)
	{
		pos[i][0] = (i*i) % 100;
		pos[i][1] = (i + i) % 100;
		forces[i][0] = 0;
		forces[i][1] = 0;
		masses[i] = 500*cos(i);
		vel[i][0] = (i % 4)/100;
		vel[i][1] = (i % 3)/100;

	}
	double x_diff, y_diff, dist, dist_cubed;
#pragma omp parallel
	for (int i = 0; i < timestep; i++)
	{
#pragma omp for
		for (int q = 0; q < particulas; q++)
		{

			for (int k = 0; k < particulas && k>q; k++)
			{
				x_diff = pos[q][X] - pos[k][X];
				y_diff = pos[q][Y] - pos[k][Y];
				dist = sqrt(x_diff*x_diff + y_diff*y_diff);
				dist_cubed = dist*dist*dist;
				forces_qk[X] = G*masses[q] * masses[k] / dist_cubed*x_diff;
				forces_qk[Y] = G*masses[q] * masses[k] / dist_cubed*y_diff;
#pragma omp critical
				forces[q][X] += forces_qk[X];
				forces[q][Y] += forces_qk[Y];
				forces[k][X] -= forces_qk[X];
				forces[k][Y] -= forces_qk[Y];
			}
		}
#pragma omp for
		for (int q = 0; q < particulas; q++)
		{
			pos[q][X] += delta*vel[q][X];
			pos[q][Y] += delta*vel[q][Y];
			vel[q][X] += delta / masses[q] * forces[q][X];
			vel[q][Y] += delta / masses[q] * forces[q][Y];

		}

	}
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

	/*linea 7
	pos[q][X]+=delta_t*vel[q][X];
	pos[q][Y]+=delta_t*vel[q][Y];
	vel[q][X]+=delta_t/masses[q][X]*forces[q][X];
	vel[q][Y]+=delta_t/masses[q][X]*forces[q][X];
	*/

    return 0;
}

