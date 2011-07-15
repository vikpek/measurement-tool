/*
 * InterfaceGnuplot.cpp
 *
 *  Created on: Jul 12, 2011
 *      Author: dogmeat
 */

#include "InterfaceGnuplot.h"

InterfaceGnuplot::InterfaceGnuplot() {
	// TODO Auto-generated constructor stub

}

InterfaceGnuplot::~InterfaceGnuplot() {
	// TODO Auto-generated destructor stub
}

void InterfaceGnuplot::plotValueFromLogEntries(char *valueName, double *values)
{
	FILE *gnuplotPipe = popen("/usr/local/bin/gnuplot -persist", "w");
	fputs("plot sin(x)/x", gnuplotPipe);
	fputc('\n', gnuplotPipe);
	pclose(gnuplotPipe);

}



