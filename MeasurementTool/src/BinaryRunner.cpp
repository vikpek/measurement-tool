/*
 * BinaryRunner.cpp
 *
 *  Created on: 03.05.2011
 *      Author: vikpek
 */

#include "BinaryRunner.h"

BinaryRunner::BinaryRunner() {
}

BinaryRunner::~BinaryRunner() {
}

LogEntry* BinaryRunner::getMeasurementLogEntries(char *binary_path,
		int quantity) {
	LogEntry *logEntries = new LogEntry[quantity];
	StringTransformer st;

//	struct rusage usage;

	pid_t pid;
	double size;
	char err_msg[] = "child_execv_error\n";

	//TODO
	//char *child_args[5];

	int err_pipe[2];
	pipe(err_pipe);

	for (int var = 0; var < quantity; ++var) {
		Timer timer;
		puts("Timer started...\n");
		/**
		 * Timer is being started right before the
		 * child process is being created and the binary started.
		 */
		timer.start();

		switch ((pid = fork())) {
		case -1:
			perror("fork error");
			break;
		case 0:
//			TODO
//			execv(binary_path, child_args);

			/*
			 * Child executes the binary.
			 */
			execv(binary_path, NULL);

			/*
			 * For the case the execution did not work out
			 * (wrong file-path for example) this part applies
			 *  and a message is being sent via pipes
			 *  to the father process.
			 */
			puts("execv error");

			close(err_pipe[0]);
			write(err_pipe[1], err_msg, (strlen(err_msg) + 1));
			_exit(EXIT_FAILURE);
			break;
		default:
			break;
		}

		int child_exit_code;

		int mem_sum = 0;
		int max_mem = 0;
		int min_mem = INT32_MAX;
		double runtime_tmp = 0;

		if (pid > 0) {

			/*
			 * Father process part. Basically this process
			 * just waits for the child and measures all
			 * requested data.
			 */
			int child_stat;
			char ps_command[100];

			sprintf(ps_command, "ps x -p %d -eo rss\n", pid);
			FILE *psPipe;
			char path[PATH_MAX];

			int i = 0;

			/*
			 * while waiting for binary-run to terminate do...
			 */
			while (waitpid(pid, &child_stat, WNOHANG) == 0) {

				psPipe = popen(ps_command, "r");
				/*
				 * 1. check memory usage for child-pid
				 */
				while (fgets(path, PATH_MAX, psPipe) != NULL) {
					if (strstr(path, "RSS")) {
						// do nothing
					} else {
						int mem_usage = atoi(path);

						/*
						 * 2. for the case the memory usage or runtime is higher than the
						 * limit set by the user, child is being killed.
						 *
						 * Causes the exit-code to be -1.
						 */

						if(max_runtime_limit>0){
							runtime_tmp = timer.getElapsedTimeInSec();
							if(runtime_tmp>max_runtime_limit){
								printf("Process terminated because of runtime limit overrun.\n %f USED / %d MAXIMUM  \n", runtime_tmp, max_runtime_limit);
								kill(pid, SIGTERM);
							}
						}
						if(max_memory_limit>0){
							if(mem_usage>max_memory_limit){
								printf("Process terminated because of memory limit overrun.\n %d USED / %d MAXIMUM  \n", mem_usage, max_memory_limit);
								kill(pid, SIGTERM);
							}
						}

						/*
						 * 3. collect data for maximum, minimum and average memory-usage.
						 */
						if (mem_usage > 0) {
							if (mem_usage > max_mem)
								max_mem = mem_usage;

							if (mem_usage < min_mem)
								min_mem = mem_usage;

							i++;
							mem_sum += mem_usage;
						}
					}
				}

			}
			mem_sum = mem_sum / i;

			/*
			 * alternative memory measure method -
			 * but does not work properly for most compilers.
			 */
//			getrusage(RUSAGE_CHILDREN, &usage);
			timer.stop();
			puts("Timer stopped.\n");

			/*
			 *if the exec call in the child process does
			 *if not start or ends unnaturally, a pipe
			 *if  message is being sent and catch here
			 */
			close(err_pipe[1]);
			char readbuffer2[30];

			read(err_pipe[0], readbuffer2, sizeof(readbuffer2));
			if (strcmp(readbuffer2, err_msg) == 0) {
				printf(
						"Error while trying to execute binary. Check binary path!");
				return NULL;
			}

			/*
			 * Analyze exit-code for child process.
			 */
			if (WIFEXITED(child_stat)) {
				child_exit_code = WIFEXITED(child_stat);
			} else {
				child_exit_code = -1;
			}
		}

		/*
		 * Size of the binary file is being measured
		 */
		ifstream binary_file(binary_path, ios::in | ios::binary | ios::ate);
		if (binary_file.is_open()) {
			size = (int) binary_file.tellg();

		}

		/*
		 * All measured information are being
		 * written in a logEntry return value.
		 */
		char* binary_name = st.returnFileNameFromPath(binary_path);

		strncpy(logEntries[var].name, binary_name, 30);
		logEntries[var].runtime = runtime_tmp;
		logEntries[var].exit_code = child_exit_code;
		logEntries[var].mem_usage = mem_sum;
		logEntries[var].size = size;
	}
	return logEntries;
}

