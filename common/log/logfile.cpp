#include "logfile.h"

#include <cstddef>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

LogFile::LogFile(LogFileIntervalType type, const std::string& perfix)
	:m_type(type), m_filePerfix(perfix)
{
	m_file = NULL;
}

LogFile::~LogFile()
{
	if (NULL != m_file)
	{
		fclose(m_file);
	}
}

void LogFile::LogPrint(LogType type, char* header, char* info)
{
	CheckFile();
	if (NULL != m_file)
	{
		fprintf(m_file, "%s%s\n", header, info);
	}
}

void LogFile::Flush()
{
	if (NULL != m_file)
	{
		fflush(m_file);
	}
}

void LogFile::CheckFile()
{
	time_t tt = time(NULL);
	struct tm* lnow = localtime(&tt);
	if (NULL != m_file)
	{
		if (TimeDiff(m_timeinfo, *lnow))
		{
			fclose(m_file);
			m_file = NULL;
		}
		else
		{
			return;
		}
	}
	else
	{
		if (-1 == access("log", F_OK))
		{
			mkdir("log", 0777);
		}
	}

	if (NULL == m_file)
	{
		m_timeinfo = *lnow;			
		char filename[128] = {'\0'};
		std::stringstream ss;
		ss << "log/" << m_filePerfix << "-%F";
		if (LFIT_HOUR == m_type || LFIT_MIN == m_type)
		{
			ss << "-%H";
			if (LFIT_MIN == m_type)
			{
				ss << "-%M";
			}
		}
		ss << ".log";
		strftime(filename, sizeof(filename), ss.str().c_str(), lnow);
		m_file = fopen(filename, "a");
		if (NULL == m_file)
		{
			printf("open %s failed\n", filename); 
		}
	}
}

bool LogFile::TimeDiff(struct tm& oldt, struct tm& newt)
{
	if (oldt.tm_year != newt.tm_year) return false;	
	if (oldt.tm_mon != newt.tm_mon) return false;
	if (oldt.tm_mday != newt.tm_mday) return false;
	if ((LFIT_HOUR == m_type || LFIT_MIN == m_type) && (oldt.tm_hour != newt.tm_hour)) return false;
	if (LFIT_MIN == m_type && oldt.tm_min != newt.tm_min) return false;

	return true;
}
