/*
 * InterfaceGnuplot.h
 *
 *  Created on: Jul 12, 2011
 *      Author: dogmeat
 */

#ifndef INTERFACEGNUPLOT_H_
#define INTERFACEGNUPLOT_H_
#include <iostream>
class InterfaceGnuplot {
public:
	InterfaceGnuplot();
	virtual ~InterfaceGnuplot();

	void plotValueFromLogEntries(char* valueName, double* values);
};

#endif /* INTERFACEGNUPLOT_H_ */