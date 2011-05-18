/*
 * SQLiteCommunicator.h
 *
 *  Created on: 08.05.2011
 *      Author: vikpek
 */
#ifndef SQLITECOMMUNICATOR_H_
#define SQLITECOMMUNICATOR_H_

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <list>
#include "LogEntry.h"

using namespace std;

class SQLiteCommunicator {
public:
	SQLiteCommunicator();
	virtual ~SQLiteCommunicator();

	int writeToDatabase(char *binary_name, list<LogEntry> logEntries);
	list<LogEntry> readLogentriesFromDatabase(char *binary_name);

private:
	int searchForTable(char *binary_name);
	int createTable(char *binary_name);
	int addToTable(char *binary_name, list<LogEntry> logEntries);

};

#endif /* SQLITECOMMUNICATOR_H_ */
