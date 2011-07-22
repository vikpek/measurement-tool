/*
 * SQLiteCommunicator.cpp
 *
 *  Created on: 08.05.2011
 *      Author: Viktor Pekar
 */

#include "SQLiteCommunicator.h"

sqlite3* db;
char* db_err;
char db_name[30] = "measurement_db.sql3";
SQLiteCommunicator::SQLiteCommunicator() {
	// TODO Auto-generated constructor stub

}

SQLiteCommunicator::~SQLiteCommunicator() {
	// TODO Auto-generated destructor stub
}

int readEntriesCallback(void *args, int numCols, char **results,
		char **columnNames) {

	int i = 0;
//	for (int var = 0; var < max; ++var) {

	for (i = 0; i < numCols; i++) {
		/* Do something with this field in the results; I guess we'll print it.*/
		printf("%s\t", results[i]);
	}
//	}
	printf("\n");
	return 1;
}

int SQLiteCommunicator::getTableSize(char *binary_name) {
	sqlite3_open(db_name, &db);
	int result = 0;
	char tmp_s[150];
	int n;
	n = sprintf(tmp_s, "select count(*) from %s", binary_name);

	const char *sqlStatement = tmp_s;
	sqlite3_stmt *compiledStatement;
	if (sqlite3_prepare_v2(db, sqlStatement, -1, &compiledStatement, NULL)
			== SQLITE_OK) {
		while (sqlite3_step(compiledStatement) == SQLITE_ROW) {
			result = sqlite3_column_int(compiledStatement, 0);
		}
	}
	sqlite3_finalize(compiledStatement);
	sqlite3_close(db);
	return result;
}

LogEntry* SQLiteCommunicator::readLogentriesFromDatabase(char *binary_name, int count) {
	LogEntry *logEntries = new LogEntry[count];
	sqlite3_open(db_name, &db);
	char tmp_s[150];
	int n;
	n = sprintf(tmp_s, "select * from %s", binary_name);
	const char *sqlStatement = tmp_s;
	sqlite3_stmt *compiledStatement;

	if (sqlite3_prepare_v2(db, sqlStatement, -1, &compiledStatement, NULL)
			== SQLITE_OK) {
		int i = 0;
		while (sqlite3_step(compiledStatement) == SQLITE_ROW) {
			const unsigned char* id = sqlite3_column_text(compiledStatement,
					0);
			const unsigned char* timestamp = sqlite3_column_text(compiledStatement,
					1);
			const unsigned char* name = sqlite3_column_text(compiledStatement,
					2);
			double runtime = sqlite3_column_double(compiledStatement,
					3);

			double size = sqlite3_column_double(compiledStatement,
					4);
			double memory_usage = sqlite3_column_double(compiledStatement,
					5);
			int exit_code = sqlite3_column_int(compiledStatement,
					6);


			logEntries[i].createLogEntry((char *) name, runtime, size, memory_usage, exit_code);
			strncpy(logEntries[i].timestamp, (char *)timestamp, 30);
			strncpy(logEntries[i].id, (char *)id, 12);
			i++;
		}
	}
	// Release the compiled statement from memory
	sqlite3_finalize(compiledStatement);

	sqlite3_close(db);

	return logEntries;
}

int SQLiteCommunicator::writeToDatabase(char *binary_name, LogEntry* logEntries,
		int quantity) {
	if (searchForTable(binary_name) == 0) {
		createTable(binary_name);
	}
	return addToTable(binary_name, logEntries, quantity);
}

/*
 * Return value 0 means no table exists.
 * 1 value means table exists.
 * -1 error.
 */
int SQLiteCommunicator::searchForTable(char *binary_name) {
	sqlite3_open(db_name, &db);
		int result = 0;
		char tmp_s[150];
		int n;
		n = sprintf(tmp_s, "select count(*) from %s", binary_name);

		const char *sqlStatement = tmp_s;
		sqlite3_stmt *compiledStatement;
		if (sqlite3_prepare_v2(db, sqlStatement, -1, &compiledStatement, NULL)
				== SQLITE_OK) {
			result = 1;
		}
		sqlite3_finalize(compiledStatement);
		sqlite3_close(db);
		return result;
}

int SQLiteCommunicator::addToTable(char *binary_name, LogEntry* logEntries_,
		int quantity) {
	sqlite3_open(db_name, &db);
	LogEntry *logEntries = new LogEntry[quantity];
	logEntries = logEntries_;
	for (int var = 0; var < quantity; ++var) {
		char tmp_s[150];
		int n;

		n =
				sprintf(
						tmp_s,
						"INSERT INTO %s  (\"name\" , \"runtime\", \"size\" , \"memory_usage\" , \"exit_code\") VALUES ( \"%s\", %f, %f, %f, %d)",
						binary_name, logEntries[var].name,
						logEntries[var].runtime, logEntries[var].size,
						logEntries[var].mem_usage, logEntries[var].exit_code);
		sqlite3_exec(db, tmp_s, NULL, 0, &db_err);
	}
	sqlite3_close(db);
	return 1;
}

int SQLiteCommunicator::createTable(char *binary_name) {

	sqlite3_open(db_name, &db);
	char tmp_s[300];
	int n;
	n =
			sprintf(
					tmp_s,
					"create table '%s' (\"id\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , \"timestamp\" DATETIME NOT NULL  DEFAULT CURRENT_TIMESTAMP, \"name\" VARCHAR NOT NULL , \"runtime\" DOUBLE DEFAULT null, \"size\" DOUBLE DEFAULT null, \"memory_usage\" DOUBLE DEFAULT null, \"exit_code\" INTEGER DEFAULT null);",
					binary_name);
	sqlite3_exec(db, tmp_s, NULL, 0, &db_err);
	sqlite3_close(db);

	return 0;
}

