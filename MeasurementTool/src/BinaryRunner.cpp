/*
 * BinaryRunner.cpp
 *
 *  Created on: 03.05.2011
 *      Author: vikpek
 */

#include "BinaryRunner.h"

BinaryRunner::BinaryRunner() {
	// TODO Auto-generated constructor stub

}

BinaryRunner::~BinaryRunner() {
	// TODO Auto-generated destructor stub
}

double BinaryRunner::getBinaryRuntime(char *binary_path, int run_cycles) {
	pid_t pid;
	double runtime;

	for (int var = 0; var < run_cycles; ++var) {

		Timer timer;
		timer.start();

		switch ((pid = fork())) {
		case -1:
			perror("fork error");
			break;
		case 0:
			//TODO parameters for binaries have to be handled
			char *child_args[5];
			execv(binary_path, child_args);
			puts("execv error");
			exit(EXIT_FAILURE);
			break;
		default:
			break;
		}

		int child_exit_code;
		if (pid != 0) {
			int child_stat;
			pid_t child_pid;

			child_pid = wait(&child_stat);

			if (WIFEXITED(child_stat)) {
				child_exit_code = WIFEXITED(child_stat);
			} else {
				child_exit_code = -1;
			}
		}
		timer.stop();
		runtime = timer.getElapsedTimeInMicroSec();

	}
	return runtime;
}

int BinaryRunner::getBinarySize(char *binary_path) {
	ifstream binary_file(binary_path, ios::in | ios::binary | ios::ate);
	int size;
	if (binary_file.is_open()) {
		size = (int) binary_file.tellg();
	}

	return size;

}
