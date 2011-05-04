/*
 * LogEntry.h
 *
 *  Created on: 04.05.2011
 *      Author: vikpek
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LOGENTRY_H_
#define LOGENTRY_H_

class LogEntry {
public:
	LogEntry();
	virtual ~LogEntry();

	void createLogEntry(time_t timestamp_, char *name_, double runtime_,
			double size_, double mem_usage_, double exit_code_);

private:
	char id[12];
	time_t timestamp;
	char name[30];
	double runtime;
	double size;
	double mem_usage;
	double exit_code;

};

#endif /* LOGENTRY_H_ */
