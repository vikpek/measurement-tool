#include "BinaryRunner.h"
#include "SQLiteCommunicator.h"
#include "LogEntry.h"
#include "StringTransformer.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "gnup/InterfaceGnuplot.h"

static void usage(const char *prgnam) {
	fprintf(
			stderr,
			"\nExecute code: %s -xy <parameter-for-measurement> binary_path -p <parameter for binary>\n",
			prgnam);
	fprintf(stderr, "\nOr try %s -help", prgnam);
	fflush(stderr);
	exit(1);
}

int main(int argc, char *argv[]) {
	int arg;
	//0 for the max values means infinite
	int max_memory = 0;
	int max_runtime = 0;
	int verbose = 0;
	int logfile = 1;
	int quantity = 1;

	if (argc < 2)
		usage(argv[0]);

	while ((arg = getopt(argc, argv, "q:m:r:l:v:a:")) != -1) {
		switch (arg) {
		case 'q':
			quantity = atoi(optarg);
			printf("Quantity set to %d \n", quantity);
			break;
		case 'r':
			max_runtime = atoi(optarg);
			printf("Maximum runtime has been set to %d \n", max_runtime);
			break;
		case 'm':
			max_memory = atoi(optarg);
			printf("Maximum memory has been set to %d \n", max_memory);
			break;
		case 'l':
			logfile = 1;
			break;

		case 'v':
			verbose = 1;
			break;

		case 'a':
			break;
		}
	}

	BinaryRunner br;
	StringTransformer st;
	SQLiteCommunicator sqlc;

	char binary_path[60];
	strcpy(binary_path, argv[1]);
	char* binary_name = st.returnFileNameFromPath(argv[1]);

	LogEntry *logEntries = new LogEntry[quantity];

	logEntries = br.getMeasurementLogEntries(binary_path, quantity);
//	le_list.push_front(le);

	sqlc.writeToDatabase(binary_name, logEntries, quantity);

	if (logfile == 1) {
		ofstream logfile;
		char path_logfile[200];
		sprintf(path_logfile, "%s_logfile.txt", binary_path);
		logfile.open(path_logfile, ios::app);
	}

	InterfaceGnuplot ig;
	int tableLength = sqlc.getTableSize(binary_name);
	LogEntry *le = sqlc.readLogentriesFromDatabase(binary_name, tableLength);

	double *values = new double[tableLength];
	for (int var = 0; var < tableLength; ++var) {
		values[var] = le[var].runtime;
	}
	char valueName[200];
	sprintf(valueName, "%s_runtime", binary_name);
	ig.plotValueFromLogEntries(valueName, values);

//	double values = new
//	ig.plotValueFromLogEntries()

	printf("Measurement successfully finished!");
	return 0;
}
