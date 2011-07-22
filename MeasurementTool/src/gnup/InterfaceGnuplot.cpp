/*
 * InterfaceGnuplot.cpp
 *
 *  Created on: Jul 12, 2011
 *      Author: Viktor Pekar
 *
 *      This interface  uses pipes for interacting with gnuplot.
 */

#include "InterfaceGnuplot.h"
#include <iostream>

InterfaceGnuplot::InterfaceGnuplot() {
	// TODO Auto-generated constructor stub

}

InterfaceGnuplot::~InterfaceGnuplot() {
	// TODO Auto-generated destructor stub
}


char* getXMode(int xmode){
	switch (xmode) {
		case 0:
			return "lines";
		case 1:
			return "dots";
		case 2:
			return "points";
		case 3:
			return "impulses";
		case 4:
			return "steps";
		default:
			break;
	}

	return "lines";

}

void InterfaceGnuplot::plotValueFromLogEntries(char *valueName, double *values, int length, int xmode,int fExport, char *exportPath)
{

	char gnuplot_command[100];
	sprintf(gnuplot_command, "/opt/local/bin/gnuplot -persist\n");
	FILE *gnuplotPipe = popen(gnuplot_command, "w");

	if(fExport == 1){
		fputs("set term gif\n", gnuplotPipe);
		char exprtPath[200];
		sprintf(exprtPath, "set out \"%s_%s.gif\" \n", exportPath, valueName);
		fputs(exprtPath, gnuplotPipe);
	}

	char title[60];
	sprintf(title, "set title \"Graph for %s for the last %d testruns\" \n", valueName, length);
	fputs(title, gnuplotPipe);
	fputs("set xlabel \"Run\" \n", gnuplotPipe);
	char ylabelTitle[30];
	sprintf(ylabelTitle, "set ylabel \"%s\" \n", valueName);
	fputs(ylabelTitle, gnuplotPipe);
	fputs("set autoscale \n", gnuplotPipe);



	char plotCommand[200];
	char* xmodeStrg = getXMode(xmode);
	sprintf(plotCommand, "plot \"-\" with %s \n", xmodeStrg);
	fputs(plotCommand, gnuplotPipe);
	for (int var = 0; var < length; ++var) {
		char strg[30];
		sprintf(strg,"%.2f \n",values[var]);

		fputs(strg, gnuplotPipe);
	}
	fputc('e', gnuplotPipe);
	fputc('\n', gnuplotPipe);
	pclose(gnuplotPipe);

}



