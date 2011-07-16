/*
 * Plotter.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: Viktor Pekar
 */

#include "Plotter.h"

Plotter::Plotter() {
	// TODO Auto-generated constructor stub

}

Plotter::~Plotter() {
	// TODO Auto-generated destructor stub
}

void Plotter::startPlotting(int plotQuantity, int tableLength,
		char *binary_name, LogEntry *le, int fExport, char* exportPath) {

	InterfaceGnuplot ig;
	double *values;
	char valueName[200];

	int quantity = tableLength;
	if (plotQuantity != 0 && plotQuantity < tableLength) {
		quantity = plotQuantity;
	}

	if (fRuntime == 1) {
		values = new double[tableLength];
		for (int var = 0; var < tableLength; ++var) {
			values[var] = le[var].runtime;
		}

		sprintf(valueName, "%s_runtime", binary_name);
		ig.plotValueFromLogEntries(valueName, values, tableLength, xmode,
				fExport, exportPath);
	}
	if (fBinarysize == 1) {
		values = new double[tableLength];
		for (int var = 0; var < tableLength; ++var) {
			values[var] = le[var].size;
		}

		sprintf(valueName, "%s_size", binary_name);
		ig.plotValueFromLogEntries(valueName, values, tableLength, xmode,
				fExport, exportPath);
	}
	if (fExitcode == 1) {
		values = new double[tableLength];
		for (int var = 0; var < tableLength; ++var) {
			values[var] = le[var].exit_code;
		}

		sprintf(valueName, "%s_exit-code", binary_name);
		ig.plotValueFromLogEntries(valueName, values, tableLength, xmode,
				fExport, exportPath);
	}
	if (fMemory == 1) {
		values = new double[tableLength];
		for (int var = 0; var < tableLength; ++var) {
			values[var] = le[var].mem_usage;
		}

		sprintf(valueName, "%s_memory", binary_name);
		ig.plotValueFromLogEntries(valueName, values, tableLength, xmode,
				fExport, exportPath);
	}
}

