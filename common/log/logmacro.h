#ifndef __LOGMACRO_H__
#define __LOGMACRO_H__

#include "logmgr.h"
#include <cstring>

#define __FILENAME__ (strrchr(__FILE__, '/') + 1)

#define LogPrintDef(Type, Fmt, ...) LogMgr::Instance()->LogPrint(Type, "%s(%s:%d): " Fmt, __FUNCTION__, __FILENAME__, __LINE__, ##__VA_ARGS__)

#define LogDebug(Fmt, ...)  LogPrintDef(LOGTYPE_DEBUG, Fmt, ##__VA_ARGS__)
#define LogInfo(Fmt, ...)  LogPrintDef(LOGTYPE_INFO, Fmt, ##__VA_ARGS__)
#define LogWarn(Fmt, ...)  LogPrintDef(LOGTYPE_WARN, Fmt, ##__VA_ARGS__)
#define LogError(Fmt, ...)  LogPrintDef(LOGTYPE_ERROR, Fmt, ##__VA_ARGS__)

#endif
