#include "logconsole.h"

static char ConsoleColor[LOGTYPE_MAX][10] =
{
	"37", //debug 白色
	"32", //info 绿色
	"33", //warn 黄色
	"31"  //error 红色
};

//stderr 无缓冲 非重定向
void LogConsole::LogPrint(LogType type, char* header, char* info)
{
	fprintf(stderr, "\033[%sm%s%s\n\033[0m", ConsoleColor[type], header, info);
}
