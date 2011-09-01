/*
 * InterfaceGnuplot.h
 *
 *  Created on: Jul 12, 2011
 *      Author: Viktor Pekar
 *
 * 		This interface  uses pipes for interacting with gnuplot.
 */

#ifndef INTERFACEGNUPLOT_H_
#define INTERFACEGNUPLOT_H_
#include <iostream>
#include <stdio.h>

class InterfaceGnuplot {
public:
	InterfaceGnuplot();
	virtual ~InterfaceGnuplot();

	void plotValueFromLogEntries(char* valueName, double* values, int length,
			int xmode, int fExport, char *exportPath);
};

#endif /* INTERFACEGNUPLOT_H_ */
