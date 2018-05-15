#ifndef __LOGCONSOLE_H__
#define __LOGCONSOLE_H__

#include "logbase.h"

class LogConsole : public LogInterface
{
public:
	virtual void LogPrint(LogType type, char* header, char* info);
	virtual void Flush() {}
};


#endif