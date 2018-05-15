#include "log_test.h"

int main()
{
	LogMgr::Instance()->Init();
	LogError("test %d", 12);
	return 0;
}
