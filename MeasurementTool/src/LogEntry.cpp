/*
 * LogEntry.cpp
 *
 *  Created on: 04.05.2011
 *      Author: Viktor Pekar
 *
 *      LogEntry is a kind of container class
 *      that stores all informations about one measurement-run.
 *
 */

#include "LogEntry.h"

LogEntry::LogEntry() {

}

LogEntry::~LogEntry() {
}

void LogEntry::createLogEntry(char *name_, double runtime_, double size_,
		double mem_usage_, double max_mem_usage_, int exit_code_) {

	strncpy(name, name_, 30);
	runtime = runtime_;
	size = size_;
	mem_usage = mem_usage_;
	max_mem_usage = max_mem_usage_;
	exit_code = exit_code_;
}

char *LogEntry::toString() {
	char *toString = (char *) calloc(2000, sizeof(char));
	sprintf(
			toString,
			"id:\t%s,\t time:\t%s,\t runtime:\t%f,\t mem:\t%f,\t max_mem:\t%f,\t size:\t%f, \t exitc:\t%d \n",
			id, timestamp, runtime, mem_usage, max_mem_usage, size, exit_code);
	return toString;
}

