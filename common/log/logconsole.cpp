#include "logconsole.h"

static char ConsoleColor[LOGTYPE_MAX][10] =
{
	"37", //debug ��ɫ
	"32", //info ��ɫ
	"33", //warn ��ɫ
	"31"  //error ��ɫ
};

//stderr �޻��� ���ض���
void LogConsole::LogPrint(LogType type, char* header, char* info)
{
	fprintf(stderr, "\033[%sm%s%s\n\033[0m", ConsoleColor[type], header, info);
}
