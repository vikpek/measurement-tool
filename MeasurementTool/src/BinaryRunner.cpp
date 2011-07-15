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

LogEntry* BinaryRunner::getMeasurementLogEntries(char *binary_path,
		int quantity) {
	LogEntry *logEntries = new LogEntry[quantity];
	StringTransformer st;

	pid_t pid;
	double size;

	for (int var = 0; var < quantity; ++var) {
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

		char* binary_name = st.returnFileNameFromPath(binary_path);
		strncpy(logEntries[var].name, (char *)binary_name, 30);
		logEntries[var].runtime = timer.getElapsedTimeInMicroSec();

		ifstream binary_file(binary_path, ios::in | ios::binary | ios::ate);
		if (binary_file.is_open()) {
			size = (int) binary_file.tellg();
		}
		logEntries[var].exit_code = child_exit_code;

	}
	return logEntries;
}

