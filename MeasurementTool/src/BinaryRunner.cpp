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

//	struct rusage usage;

	pid_t pid;
	double size;
	char err_msg[] = "child_execv_error\n";

	char *child_args[5];

	int err_pipe[2];
	pipe(err_pipe);

	for (int var = 0; var < quantity; ++var) {
		Timer timer;

		puts("Timer started...\n");
		timer.start();
		switch ((pid = fork())) {
		case -1:
			perror("fork error");
			break;
		case 0:
//			execv(binary_path, child_args);
			execv(binary_path, NULL);
			puts("execv error");

			close(err_pipe[0]);
			write(err_pipe[1], err_msg, (strlen(err_msg) + 1));
			_exit(EXIT_FAILURE);
			break;
		default:
			break;
		}

		int child_exit_code;
		int child_pid;

		int mem_sum = 0;
		int max_mem = 0;
		int min_mem = INT32_MAX;

		int status;
		if (pid > 0) {
			int child_stat;
			char ps_command[100];

			sprintf(ps_command, "ps x -p %d -eo rss\n", pid);
			FILE *psPipe;
			char path[PATH_MAX];

			int i = 0;

			while(waitpid(pid, &child_stat, WNOHANG) == 0){
				psPipe = popen(ps_command, "r");
				while (fgets(path, PATH_MAX, psPipe) != NULL){
					if(strstr(path, "RSS")){
						//skip it
					}else{
					    int mem_usage = atoi(path);
					    if(mem_usage >0){
					    	if(mem_usage>max_mem)
					    		max_mem = mem_usage;

					    	if(mem_usage < min_mem)
					    		min_mem = mem_usage;

					    	i++;
					    	mem_sum += mem_usage;
					    }
					}
				}

			}
			mem_sum  = mem_sum/i;
			printf("Average: %d Max: %d Min: %d \n", mem_sum, max_mem, min_mem);
//			getrusage(RUSAGE_CHILDREN, &usage);
			timer.stop();
			puts("Timer stopped.\n");

			close(err_pipe[1]);

			char readbuffer2[30];

			read(err_pipe[0], readbuffer2, sizeof(readbuffer2));
			if (strcmp(readbuffer2, err_msg) == 0) {
				printf(
						"Error while trying to execute binary. Check binary path!");
				return NULL;
			}

			if (WIFEXITED(child_stat)) {
				child_exit_code = WIFEXITED(child_stat);
			} else {
				child_exit_code = -1;
			}
		}

		char* binary_name = st.returnFileNameFromPath(binary_path);
		strncpy(logEntries[var].name, binary_name, 30);

		logEntries[var].runtime = timer.getElapsedTimeInSec();

		ifstream binary_file(binary_path, ios::in | ios::binary | ios::ate);
		if (binary_file.is_open()) {
			size = (int) binary_file.tellg();
			logEntries[var].size = size;
		}
		logEntries[var].exit_code = child_exit_code;
		logEntries[var].mem_usage = mem_sum;

	}
	return logEntries;
}

