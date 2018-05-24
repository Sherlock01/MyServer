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

#endif

