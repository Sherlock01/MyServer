#ifndef __NET_HANDLER_H__
#define __NET_HANDLER_H__

#include "net_def.h"
#include "mem_pool.h"
#include "ptr_pipe.h"

class NetHandler
{
public:
	NetHandler();
	~NetHandler();

	void Update();		

	int ReqListen(uint16_t port);
	int ReqConnect(uint32_t addr, uint16_t port);
	int ReqDisConnect(ConnID connID);
	int ReqSendData(char* data, uint16_t len);

private:
	PtrPipeMgr* PipeMgr();

private:
	MemPool m_memPool;	
};

#endif

