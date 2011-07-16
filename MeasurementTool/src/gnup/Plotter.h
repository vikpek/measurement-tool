/*
 * Plotter.h
 *
 *  Created on: Jul 16, 2011
 *      Author: dogmeat
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_
#include "../LogEntry.h"
#include "InterfaceGnuplot.h"

class Plotter {
public:
	Plotter();
	virtual ~Plotter();
	void startPlotting(int plotQuantity, int tableSize, char* binary_name, LogEntry *le, int fExport, char* exportPath);

	int xmode;
	int fRuntime;
	int fMemory;
	int fExitcode;
	int fBinarysize;

};

#endif /* PLOTTER_H_ */
