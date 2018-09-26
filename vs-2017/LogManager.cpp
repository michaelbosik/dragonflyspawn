//
//LogManager.cpp
//

#include "LogManager.h"
#include "stdarg.h"
#include "stdio.h"
#include "utility.h"

df::LogManager::LogManager() {
	setType("LogManager");
}

// If logfile is open, close it.
df::LogManager::~LogManager() {
	if (m_p_f != NULL) //Check if the logfile isnt NULL
		fclose(m_p_f);
}

df::LogManager::LogManager(LogManager const&) {}

void df::LogManager::operator=(LogManager const&) {}

// Get the one and only instance of the LogManager.
df::LogManager &df::LogManager::getInstance() {
	static LogManager logManager;
	return logManager;
}

// Start up LogManager (open main logfile, usually "dragonfly.log").
// Return 0 if ok, else -1.
int df::LogManager::startUp() {
	m_p_f = fopen(LOGFILE_DEFAULT.c_str(), "w");
	if (m_p_f == NULL)
		return 0;
	return -1;
}

// Shut down LogManager (close all logfiles).
void df::LogManager::shutDown() {
	fclose(m_p_f);
}

// Write to logfile.
// Supports printf() formatting of strings.
// Return number of bytes written (excluding prepends), -1 if error.
int df::LogManager::writeLog(const char *fmt, ...) const {

	fprintf(m_p_f, "%s >", df::getTimeString()); //Message header
	va_list logList; 
	va_start(logList, fmt); 
	vfprintf(m_p_f, fmt, logList); //Add contents of fmt to the logfile
	va_end(logList);
	fprintf(m_p_f, "\n"); //Make a new line in the logfile

	if (m_do_flush) //Flush the logfile if user elected to
		fflush(m_p_f);

	return -1;
}

// Set flush of logfile after each write.
void df::LogManager::setFlush(bool new_do_flush) {
	m_do_flush = new_do_flush;
}