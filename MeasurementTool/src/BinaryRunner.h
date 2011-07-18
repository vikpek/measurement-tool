/*
 * BinaryRunner.h
 *
 *  Created on: 03.05.2011
 *      Author: vikpek
 */

#include "Timer.h"
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "LogEntry.h"
#include <iostream>
#include <fstream>
#include <list>
#include "StringTransformer.h"

using namespace std;

#ifndef BINARYRUNNER_H_
#define BINARYRUNNER_H_

class BinaryRunner {
public:
	BinaryRunner();
	virtual ~BinaryRunner();

	LogEntry* getMeasurementLogEntries(char *binary_path, int quantity);

};

#endif /* BINARYRUNNER_H_ */
