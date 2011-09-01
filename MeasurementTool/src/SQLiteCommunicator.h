/*
 * SQLiteCommunicator.h
 *
 *  Created on: 08.05.2011
  *      Author: Viktor Pekar
 */
#ifndef SQLITECOMMUNICATOR_H_
#define SQLITECOMMUNICATOR_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sqlite3.h>
#include <list>
#include "LogEntry.h"

using namespace std;

class SQLiteCommunicator {
public:
	SQLiteCommunicator();
	virtual ~SQLiteCommunicator();

	int getTableSize(char *binary_name);
	int writeToDatabase(char *binary_name, LogEntry* logEntries, int quantity);
	LogEntry* readLogentriesFromDatabase(char *binary_name, int count);


private:
	int searchForTable(char *binary_name);
	int createTable(char *binary_name);
	int addToTable(char *binary_name, LogEntry *logEntries, int quantity);

};

#endif /* SQLITECOMMUNICATOR_H_ */
