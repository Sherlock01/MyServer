#ifndef __NETDEF_H__
#define __NETDEF_H__

#include <cstdint>

typedef uint16_t ConnID;

enum HNetReqType
{
	HNRT_LISTEN,
	HNRT_CONNECT,
	HNRT_DISCONNECT,
	HNRT_SENDDATA,
};

struct HNetReqListen
{
	uint16_t port;
};

struct HNetReqConnect 
{
	uint32_t addr;
	uint16_t port;
};

struct HNetReqDisConnect
{
	ConnID connID;
};

struct HNetReqSendData
{
	ConnID connID;
	uint16_t len;
	char data[0];
};

struct HNetReqInfo
{
	HNetReqType type;
	union 
	{
		HNetReqListen listen;
		HNetReqConnect connect;
		HNetReqDisConnect disconnect;
		HNetReqSendData senddata;
	}info;
};

namespace HNET//HNetFuncRet
{
	//成功为非负数 失败为负数
	enum
	{
		FUNC_F_ONEWAY_PTRTMPFULL = -2,
		FUNC_FAILED = -1,
		FUNC_SUCCESS = 0,
		FUNC_S_ONEWAY_INTO_PTRTMP = 1,
	};
}

#endif

