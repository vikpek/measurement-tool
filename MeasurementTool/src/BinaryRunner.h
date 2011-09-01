/*
 * BinaryRunner.h
 *
 *  Created on: 03.05.2011
 *      Author: Viktor Pekar
 *
 *      The main measurement class. Basically a process
 *      starts a child-process that runs the binary. The
 *      father process measures the child while runtime.
 *
 *      Afterwards all information are stored and returned
 *      as an LogEntry-entity.
 */

#include "Timer.h"
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
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

	int measure_intervall;

	int max_memory_limit;
	int max_runtime_limit;

	LogEntry* getMeasurementLogEntries(char *binary_path, int quantity);

};

#endif /* BINARYRUNNER_H_ */
