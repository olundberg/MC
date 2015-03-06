#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "Headers/Update.h"
#include "Headers/Magnetization.h"
#include "Headers/Energy.h"

int main(void){
    /* Open file to write values in */
	FILE *fp;
	fp =fopen("DataFrame.csv","w+");


    /* Initialize variables */
	double ETemp, E, E2;
	double MTemp, m , m2, m4;
	double L3 = 12*12*12, t, Cv = 0;
	int StartMeasureAfter = 10000, lattice[12][12][12] = {{{0}}}, MCSMax = 100000, Sweep;
	double g = 0, tMax = 0, CvMax = 0, Xi = 0;

    /* Set seed */
	srand(1);
	srand48(1);

    /* Print header */
    printf("Running with 12-sized lattice    \n");
	printf("Temp     Energy    Cv       Xi          g    \n");
	
	/* Start a loop for a given temperature to simulate for */
	for	(t = 0.000; t <= 3.000; t = t + 0.005)
	{
	    /* Reset all values for every temperature simulated */
		E = E2 = 0;
		m = m2 = m4 = 0;
		Cv = 0;
		g = 0;
		Xi = 0;

        /* Perform simulation for MCS's */
		for (Sweep = 1; Sweep <= MCSMax; Sweep++)
		{
			if (Sweep > StartMeasureAfter)
			{
			    /* Calculate magnetization and energy for a lattice */
				ETemp = Energy(lattice);
				E += ETemp;
				E2 = E2 + (ETemp*ETemp);
				MTemp = Magnetization(lattice);
				m = m + MTemp;
				m2 = m2 + (MTemp*MTemp);
				m4 = m4 + (MTemp*MTemp*MTemp*MTemp);
			}
			
			/* Update lattice and present percentage done */
			Update(lattice, t);
			printf("%.0f%%\r", (float) Sweep/MCSMax*100);
		}


        /* Calculate mean values  after thermalization */
		E = E/(MCSMax-StartMeasureAfter);
		E2 = E2/(MCSMax-StartMeasureAfter);
		m = m/(MCSMax-StartMeasureAfter);
		m2 = m2/(MCSMax-StartMeasureAfter);
		m4 = m4/(MCSMax-StartMeasureAfter);
		
		
		/* Calculate Xi, Cv, g */
        	Xi = (m2-m*m);
		Cv = (E2-E*E);
		g = 1 - (m4)/(3*m2*m2);
		
		
		/* temperature, Energy, Cv, Susceptibility, Binder and Magnetization are printed */
		printf("%.4f   %.4f   %.4f   %.10lf   %.6f %f \n" , t, E/L3, Cv/L3, Xi/L3, g,m);
		fprintf(fp,"%f,%f,%f,%.10lf,%f,%f \n" , t, E/L3, Cv/L3, Xi/L3, g,m);
		
		
		/* Find critial temperature */
		if (Cv > CvMax)
		{ 
		    tMax = t;
		    CvMax = Cv;
		}

	}
	
	/* End */
    printf("Critical temperature: %.4f\n", tMax);
	fclose(fp);
	return 0;
}
