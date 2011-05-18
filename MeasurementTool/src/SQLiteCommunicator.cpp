/*
 * SQLiteCommunicator.cpp
 *
 *  Created on: 08.05.2011
 *      Author: vikpek
 */

#include "SQLiteCommunicator.h"

sqlite3* db;
char* db_err;

SQLiteCommunicator::SQLiteCommunicator() {
	// TODO Auto-generated constructor stub

}

SQLiteCommunicator::~SQLiteCommunicator() {
	// TODO Auto-generated destructor stub
}

list<LogEntry> SQLiteCommunicator::readLogentriesFromDatabase(char *binary_name) {
	list<LogEntry> logEntries;
	if (searchForTable(binary_name) == 0) {
		return logEntries;
	} else {
		//TODO
	}
	return logEntries;
}

int SQLiteCommunicator::writeToDatabase(char *binary_name,
		list<LogEntry> logEntries) {
	if (searchForTable(binary_name) == 0) {
		createTable(binary_name);
	}
	return addToTable(binary_name, logEntries);
}

/*
 * Return value 0 means no table exists.
 * 1 value means table exists.
 * -1 error.
 */
int SQLiteCommunicator::searchForTable(char *binary_name) {
	//TODO
	return 0;
}

int SQLiteCommunicator::addToTable(char *binary_name, list<LogEntry> logEntries) {
	sqlite3_open("my_db.sql3", &db);
	LogEntry le;
	for (list<LogEntry>::iterator it = logEntries.begin(); it
			!= logEntries.end(); it++) {

		le = *it;
		char tmp_s[50];
		int n;
		n
				= sprintf(
						tmp_s,
						"INSERT INTO ft  (\"name\" , \"runtime\", \"size\" , \"memory_usage\" , \"exit_code\") VALUES ( \"%s\", %f, %f, %f, %d)",
						le.name, le.runtime, le.size, le.mem_usage,
						le.exit_code);
		sqlite3_exec(db, tmp_s, NULL, 0, &db_err);
	}
	sqlite3_close(db);
	return 1;
}

int SQLiteCommunicator::createTable(char *binary_name) {

	sqlite3_open("my_db.sql3", &db);
	char tmp_s[300];
	int n;
	n
			= sprintf(
					tmp_s,
					"create table '%s' (\"id\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , \"timestamp\" DATETIME NOT NULL  DEFAULT CURRENT_TIMESTAMP, \"name\" VARCHAR NOT NULL , \"runtime\" DOUBLE DEFAULT null, \"size\" DOUBLE DEFAULT null, \"memory_usage\" DOUBLE DEFAULT null, \"exit_code\" INTEGER DEFAULT null);",
					binary_name);
	sqlite3_exec(db, tmp_s, NULL, 0, &db_err);
	sqlite3_close(db);

	return 0;
}

