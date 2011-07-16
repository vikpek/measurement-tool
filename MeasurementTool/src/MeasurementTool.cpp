#include "BinaryRunner.h"
#include "SQLiteCommunicator.h"
#include "LogEntry.h"
#include "StringTransformer.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "gnup/Plotter.h"

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

	// maximum memory per testrun in bytes. 0 is default and means no limit.
	int max_memory = 0;
	// maximum runtime per testrun in seconds. 0 is default and means no limit.
	int max_runtime = 0;
	// verbose mode is disabled by default
	int flag_verbose = 0;
	// logfile is enabled by default
	int flag_logfile = 1;
	// defines the number of testruns
	int quantity = 1;
	// plotting mode is disabled by default
	int flag_plotting = 0;
	// defines how many old run-data will be plotted - 0 means all in db
	int plotQuantity = 0;
	// defines if export to image is enabled.
	int flag_export = 0;
	//defines gnuplot-style
	int xmode = 0;

	//flags for parameters that should be plotted
	int flag_xRuntime = 1;
	int flag_xMemory = 1;
	int flag_xBinary_size = 0;
	int flag_xExit_code = 0;

	char *binary_path = NULL;
	binary_path = (char *) calloc(300, sizeof(char));

	if (argc < 2)
		usage(argv[0]);
	int c;
	while (1) {
        static struct option long_options[] =
          {
            /* These options set a flag. */
            {"logging-enabled", no_argument,       &flag_logfile, 1},
            {"logging-disabled",   no_argument,       &flag_logfile, 0},
            {"export-enabled", no_argument,       &flag_export, 1},
            {"export-disabled",   no_argument,       &flag_export, 0},
            {"verbose", no_argument,       &flag_verbose, 1},
            {"brief",   no_argument,       &flag_verbose, 0},
            /* These options don't set a flag.
               We distinguish them by their indices. */
            {"binary-path",  required_argument, 0, 'p'},
            {"quantity",  required_argument, 0, 'q'},
            {"maximum-runtime",    required_argument, 0, 'r'},
            {"maximum-memory",    required_argument, 0, 'm'},
            {"plotting-range",    required_argument, 0, 'g'},
            {"plotting-style",    required_argument, 0, 'x'},
            {"plotting-parameters",    required_argument, 0, 'h'},
            {0, 0, 0, 0}
          };
		int option_index = 0;

		c = getopt_long(argc, argv, "vp:lq:x:m:r:b:eg:", long_options,
				&option_index);

		if(c == -1)
			break;

		switch (c) {
		case 'p':
//			strcpy(binary_path, optarg);
			binary_path = optarg;
			break;
		case 'q':
			quantity = atoi(optarg);
			if(quantity<1){
				printf("Quantity value not valid. Set to 1 instead.");
				quantity = 1;
			}
			printf("Quantity set to %d \n", quantity);
			break;
		case 'r':
			max_runtime = atoi(optarg);
			if(max_runtime<1){
				printf("Maximum runtime parameter not valid. Set to infinite instead.");
				max_runtime = 0;
			}
			printf("Maximum runtime has been set to %d \n", max_runtime);
			break;
		case 'm':
			max_memory = atoi(optarg);
			if(max_memory<1){
				printf("Maximum memory parameter not valid. Set to infinite instead.");
				max_memory = 0;
			}
			printf("Maximum memory has been set to %d \n", max_memory);
			break;
		case 'l':
			flag_logfile = 1;
			printf("Logfile enabled \n");
			break;
		case 'g':
			flag_plotting = 1;
			plotQuantity = atoi(optarg);
			printf("Plotting enabled \n");
			break;
		case 'x':
			xmode = atoi(optarg);
			printf("XMode set \n");
			break;
		case 'v':
			flag_verbose = 1;
			break;
		case 'e':
			flag_export = 1;
			break;
		case 'h':

			break;

		case '?':
			if (optopt == 'p') {
				printf("Plotting set to default parameters \n");
				flag_plotting = 1;
				xmode = 0;
				plotQuantity = 0;
			}
			if (optopt == 'x') {
				printf(
						"gnuplot style set to default because no styleparam entered \n");
			}
			break;
		case 'a':
			break;
		}
	}

	if(flag_export==1){
		if(flag_plotting == 0){
			flag_plotting = 1;
		}
	}

	BinaryRunner br;
	StringTransformer st;
	SQLiteCommunicator sqlc;

	char* binary_name = NULL;
	binary_name = (char *) calloc(100, sizeof(char));
	binary_name = st.returnFileNameFromPath(binary_path);

	LogEntry *logEntries = new LogEntry[quantity];

	logEntries = br.getMeasurementLogEntries(binary_path, quantity);
//	le_list.push_front(le);

	sqlc.writeToDatabase(binary_name, logEntries, quantity);

	if (flag_logfile == 1) {
		ofstream logfile;
		char path_logfile[200];
		sprintf(path_logfile, "%s_logfile.txt", binary_path);
		logfile.open(path_logfile, ios::app);
	}

	//todo
	flag_plotting = 1;
	if (flag_plotting == 1) {
		Plotter plotter;

		//todo dynamic.
		plotter.xmode = 0;
		plotter.fBinarysize = flag_xBinary_size;
		plotter.fRuntime = flag_xRuntime;
		plotter.fExitcode = flag_xExit_code;
		plotter.fMemory = flag_xMemory;

		int tableLength = sqlc.getTableSize(binary_name);
		LogEntry *le = sqlc.readLogentriesFromDatabase(binary_name,
				tableLength);

		plotter.startPlotting(plotQuantity, tableLength, binary_name, le, 0,
				binary_path);
		if (flag_export == 1) {
			printf("Export of Graphs to %s", binary_path);
			plotter.startPlotting(plotQuantity, tableLength, binary_name, le, 1,
					binary_path);
		}
	}

	printf("Measurement successfully finished!");
	return 0;
}
