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
	if (!m_epollMgr.Init())
	{
		return false;
	}
	return true;
}

void NetThread::UnInit()
{
	m_epollMgr.UnInit();
}

void NetThread::Update()
{
	m_netEvents.Update();
	m_epollMgr.Update();
}
