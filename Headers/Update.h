void Update(int lattice[12][12][12],double t)
{
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Initialize local variables */
int i, j, k, TempVal;
int dimensions = 12, hold, hnew;
int len = 12;
int deltah;

/* Walk over lattice to update lattice through hamiltonian */
for (i = 1; i <= dimensions; i++)
{
    for (j = 1; j <= dimensions; j++)
    {
        for (k = 1; k <= dimensions; k++)
        {
            /* Set to 0 for every site */
        	hold = 0;
        	hnew = 0;
        	deltah = 0;

            /* Random integer 0, 1 or 2 */
        	TempVal = (int) rand() % 3;

            /* Calculate old hamiltonian */
        	if (lattice[i-1][j-1][k-1] == lattice[i%len][j-1][k-1]){
        		hold -= 1;
        	}
        	if (lattice[i-1][j-1][k-1] == lattice[i-1][j%len][k-1]){
        		hold -= 1;
        	}
        	if (lattice[i-1][j-1][k-1] == lattice[i-1][j-1][k%len]){
        		hold -= 1;
        	}
        	if (lattice[i-1][j-1][k-1] == lattice[(i-2)%len][j-1][k-1]){
        		hold -= 1;
        	}
        	if (lattice[i-1][j-1][k-1] == lattice[i-1][(j-2)%len][k-1]){
        		hold -= 1;
        	}
        	if (lattice[i-1][j-1][k-1] == lattice[i-1][j-1][(k-2)%len]){
        		hold -= 1;
        	}

            /* Calculate new hamiltonian */
        	if (TempVal == lattice[i%len][j-1][k-1]) {
        		hnew -= 1;
        	} if (TempVal == lattice[i-1][j%len][k-1]) {
        		hnew -= 1;
        	} if (TempVal == lattice[i-1][j-1][k%len]) {
        		hnew -= 1;
        	} if (TempVal == lattice[(i-2)%len][j-1][k-1]) {
        		hnew -= 1;
        	} if (TempVal == lattice[i-1][(j-2)%len][k-1]) {
        		hnew -= 1;
        	} if (TempVal == lattice[i-1][j-1][(k-2)%len]) {
        		hnew -= 1;
        	}

            /* Calculate difference and se if accept or reject */
            deltah = hnew - hold;
        	if (deltah < 0) 
        	{
        	    lattice[i-1][j-1][k-1] = TempVal;
        	}
            else if (exp(-(deltah)/t) > drand48())
            {
            		lattice[i-1][j-1][k-1] = TempVal;
        	}

        }
    }
}

}
