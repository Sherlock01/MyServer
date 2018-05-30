#ifndef __NET_THREAD_H__
#define __NET_THREAD_H__

#include "mythread.h"

#include "ptr_pipe.h"
#include "epollmgr.h"
#include "net_events.h"
#include "socketmgr.h"

class NetThread : public Thread
{
public:
	NetThread();
	~NetThread();
	 
	bool Init();
	void UnInit();

	void Update();

    virtual void Run();

	inline PtrPipeMgr& GetPipeMgr() { return m_pipeMgr; }
	inline SocketMgr& GetSocketMgr() { return m_socketMgr; }
	inline EpollMgr& GetEpollMgr() { return m_epollMgr; }
private:
	
private:
	EpollMgr m_epollMgr;
	NetEvents m_netEvents;		
	SocketMgr m_socketMgr;
	PtrPipeMgr m_pipeMgr;
};

#endif

