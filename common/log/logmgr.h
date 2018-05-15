#ifndef __LOGMGR_H__
#define __LOGMGR_H__

#include "singleton.h"
#include "logbase.h"

#include <cstddef>
#include <cstdint>

enum LogPrintType
{
	LOGPRINT_CONSOLE,
	LOGPRINT_FILE,

	LOGPRINT_MAX,
};

class LogMgr : public Singleton<LogMgr>
{
public:
	LogMgr();
	~LogMgr();

	bool Init();	

	void LogPrint(LogType type, const char* fmt, ...);

private:
	void Flush();

private:
	LogType m_logLevel;
	LogInterface* m_logList[LOGPRINT_MAX];

	char* m_buffer;
	uint32_t m_bufferLen;
};

#endif
