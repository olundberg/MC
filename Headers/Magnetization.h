double Magnetization(int lattice[12][12][12])
{

/* Initialize local variables */
int i, j, k, len = 12;
double magnetization = 0, nmax = 0;
double n0 = 0, n1 = 0, n2 = 0;
double L3 = 12*12*12;

/* Walk over lattice to check state */
for (i = 1; i <= len; i++)
{
    for (j = 1; j <= len; j++)
    {
        for (k = 1; k <= len; k++)
        {
        	if (lattice[i-1][j-1][k-1] == 0)
        	{
        		n0 = n0 + 1;
        	}

        	if (lattice[i-1][j-1][k-1] == 1)
        	{
        		n1 = n1 + 1;
        	}

        	if (lattice[i-1][j-1][k-1] == 2)
        	{
        		n2 = n2 + 1;
        	}
        }
    }
}

nmax = n0;

if (n1 > nmax)
{
	nmax = n1;
}

if (n2 > nmax)
{
	nmax = n2;
}

magnetization = (nmax-(L3-nmax)/2);

return magnetization;
}
