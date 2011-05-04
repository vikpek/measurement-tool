/*
 * MySqlCommunicator.h
 *
 *  Created on: 04.05.2011
 *      Author: vikpek
 */

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "LogEntry.h"

using namespace std;

#ifndef MYSQLCOMMUNICATOR_H_
#define MYSQLCOMMUNICATOR_H_

class MySqlCommunicator {
public:
	MySqlCommunicator();
	virtual ~MySqlCommunicator();

	void addLogEntriesToDatabase(LogEntry *logEntries);

private:
	void connectToDatabase();
};

#endif /* MYSQLCOMMUNICATOR_H_ */
