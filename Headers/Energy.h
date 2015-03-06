double Energy(int lattice[12][12][12])
{

/* Initialize local variables */
int i, j, k, len = 12;
double energy = 0;

/* Walk over lattice to calculate energy */
for (i = 1; i <= len; i++)
{
    for (j = 1; j <= len; j++)
    {
        for (k = 1; k <= len; k++)
        {
        	if (lattice[i-1][j-1][k-1] == lattice[i%len][j-1][k-1])
        	{
        		energy -= 1;
        	}

        	if (lattice[i-1][j-1][k-1] == lattice[i-1][j%len][k-1])
        	{
        		energy -= 1;
        	}

        	if (lattice[i-1][j-1][k-1] == lattice[i-1][j-1][k%len])
        	{
        		energy -= 1;
        	}
        }
    }
}

return energy;
}
