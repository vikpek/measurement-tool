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
	struct rusage usage;

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
			char *child_args[5];
			execv(binary_path, child_args);
			_exit(EXIT_FAILURE);
			puts("execv error");
			exit(EXIT_FAILURE);
			break;
		default:
			break;
		}

		int child_exit_code;

		int status;
		if (pid > 0) {

			int child_stat;
			while (1) {
				if (wait(&child_stat)) {
					printf("if yeah\n");
					break;
				}else{
					printf("no hell \n");
				}

			}

			getrusage(RUSAGE_CHILDREN, &usage);

			timer.stop();
//			getrusage(RUSAGE_CHILDREN,&usage);

			if (WIFEXITED(child_stat)) {
				child_exit_code = WIFEXITED(child_stat);
			} else {
				child_exit_code = -1;
			}
		}

		char* binary_name = st.returnFileNameFromPath(binary_path);

		long t = usage.ru_ixrss;
		long t2 = usage.ru_idrss;
		long t3 = usage.ru_isrss;

		printf("%lu.%lu\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);

		strncpy(logEntries[var].name, binary_name, 30);
		double test = timer.getElapsedTimeInSec();
		logEntries[var].runtime = timer.getElapsedTimeInSec();
//		timer.getElapsedTimeInSec()

		ifstream binary_file(binary_path, ios::in | ios::binary | ios::ate);
		if (binary_file.is_open()) {
			size = (int) binary_file.tellg();
			logEntries[var].size = size;
		}

		logEntries[var].exit_code = child_exit_code;

	}
	return logEntries;
}

