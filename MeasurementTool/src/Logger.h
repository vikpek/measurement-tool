/*
 * Logger.h
 *
 *  Created on: 04.05.2011
 *      Author: vikpek
 */

#include <list>
#include "LogEntry.h"

using namespace std;

#ifndef LOGGER_H_
#define LOGGER_H_

class Logger {
public:
	Logger();
	virtual ~Logger();

	void addLogEntry(LogEntry le_);
	void printOutLog();

private:
	list<LogEntry> logEntries;
};

#endif /* LOGGER_H_ */
