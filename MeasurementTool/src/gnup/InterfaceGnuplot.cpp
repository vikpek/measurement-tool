/*
 * InterfaceGnuplot.cpp
 *
 *  Created on: Jul 12, 2011
 *      Author: dogmeat
 */

#include "InterfaceGnuplot.h"
#include <iostream>

InterfaceGnuplot::InterfaceGnuplot() {
	// TODO Auto-generated constructor stub

}

InterfaceGnuplot::~InterfaceGnuplot() {
	// TODO Auto-generated destructor stub
}

void InterfaceGnuplot::plotValueFromLogEntries(char *valueName, double *values, int length)
{
//	set title "Cavendish Data"
//	set xlabel "Time (s)"
//	set ylabel "Angle (mrad)"
//	set grid
//	set   autoscale                        # scale axes automatically
//	      unset log                              # remove any log-scaling
//	      unset label                            # remove any previous labels
//	      set xtic auto                          # set xtics automatically
//	      set ytic auto                          # set ytics automatically
//	      set title "Force Deflection Data for a Beam and a Column"
//	      set xlabel "Deflection (meters)"
//	      set ylabel "Force (kN)"
//	      set key 0.01,100
//	      set label "Yield Point" at 0.003,260
//	      set arrow from 0.0028,250 to 0.003,280
//	      set xr [0.0:0.022]
//	      set yr [0:325]

	FILE *gnuplotPipe = popen("/usr/local/bin/gnuplot -persist", "w");
	fputs("plot \"-\" with linespoints \n", gnuplotPipe);
	for (int var = 0; var < length; ++var) {
		char strg[30];
		sprintf(strg,"%.2f \n",values[var]);

		fputs(strg, gnuplotPipe);
	}
	fputc('e', gnuplotPipe);
	fputc('\n', gnuplotPipe);
	pclose(gnuplotPipe);

}



