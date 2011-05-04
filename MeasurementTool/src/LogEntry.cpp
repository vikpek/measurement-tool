/*
 * LogEntry.cpp
 *
 *  Created on: 04.05.2011
 *      Author: vikpek
 */

#include "LogEntry.h"

LogEntry::LogEntry() {
	// TODO Auto-generated constructor stub

}

LogEntry::~LogEntry() {
	// TODO Auto-generated destructor stub
}

void LogEntry::createLogEntry(time_t timestamp_, char *name_, double runtime_,
		double size_, double mem_usage_, double exit_code_) {

	timestamp = timestamp_;
	strncpy(name, name_, 30);
	runtime = runtime_;
	size = size_;
	mem_usage = mem_usage_;
	exit_code = exit_code_;


}
