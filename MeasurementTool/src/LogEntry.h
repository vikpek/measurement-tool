/*
 * LogEntry.h
 *
 *  Created on: 04.05.2011
 *      Author: Viktor Pekar
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

	char* toString();
	void createLogEntry(char *name_, double runtime_, double size_,
			double mem_usage_, double max_mem_usage_, int exit_code_);

	char id[12];
	char name[30];
	char timestamp[30];
	double runtime;
	double size;
	double mem_usage;
	double max_mem_usage;
	int exit_code;

};

#endif /* LOGENTRY_H_ */
