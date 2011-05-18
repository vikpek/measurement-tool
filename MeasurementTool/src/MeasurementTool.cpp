#include "BinaryRunner.h"
#include "SQLiteCommunicator.h"
#include "LogEntry.h"
#include "StringTransformer.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	BinaryRunner br;
	StringTransformer st;
	SQLiteCommunicator sqlc;

	char binary_path[60];
	strcpy(binary_path, argv[1]);
	char* binary_name = st.returnFileNameFromPath(argv[1]);

	LogEntry le;
	le.createLogEntry(binary_name,
			(br.getBinaryRuntime(binary_path, 1)), (br.getBinarySize(binary_path)),
			0.0, 0.0);

	list<LogEntry> le_list;
	le_list.push_front(le);

	sqlc.writeToDatabase(binary_name, le_list);

	//	ofstream logfile;
	//		char path_logfile[200];
	//		sprintf(path_logfile, "%s_logfile.txt", binary_path);
	//		logfile.open(path_logfile, ios::app);
	return 0;
}
