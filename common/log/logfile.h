#ifndef __LOGFILE_H__
#define __LOGFILE_H__

#include "logbase.h"
#include <string>

enum LogFileIntervalType
{
	LFIT_DAY,
	LFIT_HOUR,
	LFIT_MIN,
};

class LogFile : public LogInterface
{
public:
	LogFile(LogFileIntervalType type, const std::string& perfix);
	~LogFile();

	virtual void LogPrint(LogType type, char* header, char* info);
	virtual void Flush();

private:
	void CheckFile();
	bool TimeDiff(struct tm& oldt, struct tm& newt);

private:
	FILE* m_file;
	LogFileIntervalType m_type;
	std::string m_filePerfix;
	struct tm m_timeinfo;
};

#endif

