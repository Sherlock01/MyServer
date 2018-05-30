#include "net_thread.h"


void NetThread::Run()
{
	Update();
}

NetThread::NetThread()
{

}

NetThread::~NetThread()
{

}

bool NetThread::Init()
{
	if (!m_pipeMgr.Init())
	{
		return false;
	}
	if (!m_epollMgr.Init())
	{
		return false;
	}
	if (!m_socketMgr.Init(111))
	{
		return false;
	}
	if (!m_netEvents.Init(this))
	{
		return false;
	}
	return true;
}

void NetThread::UnInit()
{
	m_netEvents.UnInit();
	m_socketMgr.UnInit();
	m_epollMgr.UnInit();
	m_pipeMgr.UnInit();
}

void NetThread::Update()
{
	m_netEvents.Update();
	m_epollMgr.Update();
}
