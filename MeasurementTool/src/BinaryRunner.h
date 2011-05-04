/*
 * BinaryRunner.h
 *
 *  Created on: 03.05.2011
 *      Author: vikpek
 */

#include "Timer.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef BINARYRUNNER_H_
#define BINARYRUNNER_H_

class BinaryRunner {
public:
	BinaryRunner();
	virtual ~BinaryRunner();

	void getBinaryRuntime(char *binary_path, int run_cycles);
	int getBinarySize(char *binary_path);
};

#endif /* BINARYRUNNER_H_ */
