#ifndef __LOGBASE_H__
#define __LOGBASE_H__

#include <cstdio>

enum LogType
{
	LOGTYPE_DEBUG,
	LOGTYPE_INFO,
	LOGTYPE_WARN,
	LOGTYPE_ERROR,

	LOGTYPE_MAX,
};

class LogInterface
{
public:
	LogInterface() {}
	virtual ~LogInterface() {}

	virtual void LogPrint(LogType type, char* header, char* info) = 0;
	virtual void Flush() = 0;
};


#endif