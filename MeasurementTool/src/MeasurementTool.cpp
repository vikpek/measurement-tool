/*
 * MeasurementTool.cpp
 *
 *  Created on: 04.05.2011
 *      Author: Viktor Pekar
 */

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
	//defines sleeptime between measurements (default is 1 ms)
	int measure_interval = 1;

	//flags for parameters that should be plotted
	int flag_xRuntime = 1;
	int flag_xMemory = 1;
	int flag_xBinary_size = 0;
	int flag_xExit_code = 0;

	char *binary_path = NULL;
	binary_path = (char *) calloc(300, sizeof(char));

	char *output_path = NULL;
	output_path = (char *) calloc(300, sizeof(char));
	int flag_output = 0;

	if (argc < 2)
		usage(argv[0]);
	int c;
	while (1) {
		static struct option long_options[] = {
		/* These options set a flag. */
		{ "logging-enabled", no_argument, &flag_logfile, 1 }, {
				"logging-disabled", no_argument, &flag_logfile, 0 }, {
				"export-enabled", no_argument, &flag_export, 1 }, {
				"export-disabled", no_argument, &flag_export, 0 }, { "verbose",
				no_argument, &flag_verbose, 1 }, { "brief", no_argument,
				&flag_verbose, 0 },
		/* These options don't set a flag.
		 We distinguish them by their indices. */
		{ "binary-path", required_argument, 0, 'p' }, { "quantity",
				required_argument, 0, 'q' }, { "maximum-runtime",
				required_argument, 0, 'r' }, { "maximum-memory",
				required_argument, 0, 'm' }, { "plotting-range",
				required_argument, 0, 'g' }, { "plotting-style",
				required_argument, 0, 'x' }, { "plotting-parameters",
				required_argument, 0, 'h' }, { 0, 0, 0, 0 } };
		int option_index = 0;

		c = getopt_long(argc, argv, "vp:lq:x:m:r:b:eg:i:o:h", long_options,
				&option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
		case 'p':
			binary_path = optarg;
			break;

		case 'o':
			output_path = optarg;
			flag_output = 1;
			break;
		case 'q':
			quantity = atoi(optarg);
			if (quantity < 1) {
				if (flag_verbose)
					printf("Quantity value not valid. Set to 1 instead.");
				quantity = 1;
			}
			if (flag_verbose)
				printf("Quantity set to %d \n", quantity);
			break;
		case 'r':
			max_runtime = atoi(optarg);
			if (max_runtime < 1) {
				if (flag_verbose)
					printf(
							"Maximum runtime parameter not valid. Set to infinite instead.");
				max_runtime = 0;
			}
			if (flag_verbose)
				printf("Maximum runtime has been set to %d \n", max_runtime);
			break;
		case 'm':
			max_memory = atoi(optarg);
			if (max_memory < 1) {
				if (flag_verbose)
					printf(
							"Maximum memory parameter not valid. Set to infinite instead.");
				max_memory = 0;
			}
			if (flag_verbose)
				printf("Maximum memory has been set to %d \n", max_memory);
			break;
		case 'l':
			flag_logfile = 1;
			if (flag_verbose)
				printf("Logfile enabled \n");
			break;
		case 'i':
			measure_interval = atoi(optarg);
			break;
		case 'g':
			flag_plotting = 1;
			plotQuantity = atoi(optarg);
			if (flag_verbose)
				printf("Plotting enabled \n");
			break;
		case 'x':
			xmode = atoi(optarg);
			if (flag_verbose)
				printf("Gnuplot style (xmode) set to %d \n", xmode);
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
				if (flag_verbose)
					printf("Plotting set to default parameters. \n");
				flag_plotting = 1;
				xmode = 0;
				plotQuantity = 0;
			}
			if (optopt == 'x') {
				if (flag_verbose)
					printf(
							"Gnuplot style (xmode) set to default because no style parameter has been entered. \n");
			} else {
				printf("Invalid input: %c. Program aborted :-( \n", optopt);
				exit(0);
			}

			break;
		case 'a':
			break;
		}
	}

	if (flag_export == 1) {
		if (flag_plotting == 0) {
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

	// start binary testrun
	br.max_memory_limit = max_memory;
	br.max_runtime_limit = max_runtime;
	br.measure_intervall = measure_interval;
	logEntries = br.getMeasurementLogEntries(binary_path, quantity);
	if (logEntries == NULL) {
		puts("ERROR: Measurement was not successful. Program aborted.\n");
		exit(1);
	}

	if (flag_output == 0) {
		output_path = binary_path;
	}

	// db communication
	if (flag_verbose)
		puts("Writing to database...");
	sqlc.writeToDatabase(binary_name, logEntries, quantity);

	if (flag_verbose)
		puts("Successfully written to database.");
	int tableLength = sqlc.getTableSize(binary_name);
	LogEntry *le = sqlc.readLogentriesFromDatabase(binary_name, tableLength);

	if (flag_logfile == 1) {
		if (flag_verbose)
			puts("Writing Logfile");
		ofstream logfile;
		char path_logfile[200];
		sprintf(path_logfile, "%s%s_logfile.txt", output_path, binary_name);
		logfile.open(path_logfile, ios::trunc);
		if (logfile.is_open()) {
			for (int var = 0; var < tableLength; var++) {
				logfile << le[var].toString();
			}
			logfile.close();
			if (flag_verbose)
				printf("Logfile successfully written to %s \n", path_logfile);
		} else {
			printf(
					"Error while writing in logfile. Probably wrong path: %s ?\n",
					path_logfile);
			exit(0);
		}
	}

	flag_plotting = 1;
	if (flag_plotting == 1) {
		if (flag_verbose)
			puts("Plotting started...");
		Plotter plotter;

		plotter.xmode = xmode;
		plotter.fBinarysize = flag_xBinary_size;
		plotter.fRuntime = flag_xRuntime;
		plotter.fExitcode = flag_xExit_code;
		plotter.fMemory = flag_xMemory;

		plotter.startPlotting(plotQuantity, tableLength, binary_name, le, 0,
				binary_path);
		if (flag_export == 1) {
			printf("Plot export to %s\n", output_path);
			plotter.startPlotting(plotQuantity, tableLength, binary_name, le, 1,
					output_path);
		}
	}
	if (flag_verbose)
		printf("Measurement successfully finished!\n");
	return 0;
}
