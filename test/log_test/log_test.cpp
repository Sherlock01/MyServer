#include "log_test.h"

#include <unistd.h>

void LogTest()
{
	for (int i = 0; i < 8; ++i)
	{
		LogDebug("test %s %d", "debug", i);
		LogInfo("test %s %d", "info", i);
		LogWarn("test %s %d", "warn", i);
		LogError("test %s %d", "error", i);
		sleep(1);
	}
}

int main()
{
	LogMgr::Instance()->Init();
	LogTest();
	return 0;
}
