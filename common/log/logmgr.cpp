#include "logmgr.h"

#include "logfile.h"
#include "logconsole.h"

#include <cstring>
#include <cstdarg>

static char LogTypeStr[LOGTYPE_MAX][10] = 
{
	" [Debug] ",
	" [Info] ",
	" [Warn] ",
	" [Error] "
};

LogMgr::LogMgr()
{
	m_logLevel = LOGTYPE_DEBUG;
	for (int i = 0; i < LOGPRINT_MAX; ++i)
	{
		m_logList[i] = NULL;
	}
	m_bufferLen = 0;;
	m_buffer = NULL;
}

LogMgr::~LogMgr()
{
	Flush();

	delete m_buffer;
	m_buffer = NULL;
	for (int i = 0; i < LOGPRINT_MAX; ++i)
	{
		delete m_logList[i];
		m_logList[i] = NULL;
	}
}

bool LogMgr::Init()
{
	//¶ÁÅäÖÃ

	m_bufferLen = 256;
	m_buffer = new char[m_bufferLen];

	m_logLevel = LOGTYPE_DEBUG;

	m_logList[LOGPRINT_CONSOLE] = new LogConsole();
	m_logList[LOGPRINT_FILE] = new LogFile(LFIT_DAY, "server");

	return true;
}

void LogMgr::LogPrint(LogType type, const char* fmt, ...)
{
	if (type < m_logLevel || type >= LOGTYPE_MAX)
	{
		return;
	}
	if (NULL == m_buffer)
	{
		return;
	}

	time_t tt = time(NULL);
	struct tm* tnow = localtime(&tt);
	char header[32] = {'\0'};
	strftime(header, sizeof(header), "%F %T", tnow);
	strcat(header, LogTypeStr[type]);

	va_list args;
	va_start(args, fmt);
	vsnprintf(m_buffer, m_bufferLen, fmt, args);
	va_end(args);

	for (int i = 0; i < LOGPRINT_MAX; ++i)
	{
		if (m_logList[i])
		{
			m_logList[i]->LogPrint(type, header, m_buffer);
		}
	}
}

void LogMgr::Flush()
{
	for (int i = 0; i < LOGPRINT_MAX; ++i)
	{
		if (m_logList[i])
		{
			m_logList[i]->Flush();
		}
	}
}
