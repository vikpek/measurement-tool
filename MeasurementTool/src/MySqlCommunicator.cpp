/*
 * MySqlCommunicator.cpp
 *
 *  Created on: 04.05.2011
 *      Author: vikpek
 */

#include "MySqlCommunicator.h"

MYSQL *connection, mysql;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

MySqlCommunicator::MySqlCommunicator() {
	// TODO Auto-generated constructor stub

}

MySqlCommunicator::~MySqlCommunicator() {
	// TODO Auto-generated destructor stub
}

void MySqlCommunicator::addLogEntriesToDatabase(LogEntry *logEntries) {

}

void MySqlCommunicator::connectToDatabase() {
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "server18.configcenter.info",
			"web272", "aln321", "user_web_272_3", 0, 0, 0);
	if (connection == NULL) {
		puts(mysql_error(&mysql));
	}
}

