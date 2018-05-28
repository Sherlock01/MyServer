#ifndef __NET_THREAD_H__
#define __NET_THREAD_H__

#include "mythread.h"

#include "ptr_pipe.h"
#include "epollmgr.h"
#include "net_events.h"

class NetThread : public Thread
{
public:
	NetThread();
	~NetThread();
	 
	bool Init();
	void UnInit();

	void Update();

    virtual void Run();

private:
	inline PtrPipeMgr* PipeMgr() { return PtrPipeMgr::Instance(); }
	
private:
	EpollMgr m_epollMgr;
	NetEvents m_netEvents;		
};

#endif

