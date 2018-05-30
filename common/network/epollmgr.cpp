#include "epollmgr.h"

#include "socketmgr.h"
#include "listen_socket.h"
#include "connect_socket.h"

EpollCtrl::EpollCtrl()
	:m_events(NULL)
	,m_maxCount(0)
	,m_epollFd(-1)
{

}

EpollCtrl::~EpollCtrl()
{

}

bool EpollCtrl::Init(int maxCount)
{
	if (maxCount <= 0)
	{
		return false;
	}
	m_epollFd = epoll_create(maxCount);
	if (-1 == m_epollFd)
	{
		return false;
	}
	m_maxCount = maxCount;
	m_events = new struct epoll_event[m_maxCount];
	return true;
}

void EpollCtrl::UnInit()
{
	delete[] m_events;
	m_events = NULL;

	m_maxCount = 0;
	if (-1 != m_epollFd)
	{
		close(m_epollFd);
		m_epollFd = -1;
	}
}

bool EpollCtrl::Add(int sock, uint32_t e, void* ptr)
{
	struct epoll_event evt;
	evt.events = e;
	evt.data.fd = sock;
	evt.data.ptr = ptr;
	return epoll_ctl(m_epollFd, EPOLL_CTL_ADD, sock, &evt) == 0;
}

bool EpollCtrl::Del(int sock)
{
	struct epoll_event evt;
	return epoll_ctl(m_epollFd, EPOLL_CTL_DEL, sock, &evt) == 0;
}

int EpollCtrl::Wait(int msec)
{
	return epoll_wait(m_epollFd, m_events, m_maxCount, msec);
}

struct epoll_event* EpollCtrl::GetEvent(int index)
{
	if (index < 0 || index >= m_maxCount)
	{
		return NULL;
	}
	return m_events[index];
}

EpollMgr::EpollMgr()
{

}

EpollMgr::~EpollMgr()
{

}

bool EpollMgr::Init()
{
	if (!m_epollCtrl.Init(1024))
	{
		return false;
	}
	return true;
}

void EpollMgr::UnInit()
{
	m_epollCtrl.UnInit();
}

void EpollMgr::Update()
{

}

bool EpollMgr::AddListenSocket(ListenSocket* netSocket)
{
	return m_epollCtrl.Add(netSocket->GetSockFd(), EPOLLIN|EPOLLET, netSocket);
}

bool EpollMgr::AddConnectSocket(ConnectSocket* netSocket)
{
	return m_epollCtrl.Add(netSocket->GetSockFd(), EPOLLIN|EPOLLOUT|EPOLLET, netSocket);
}

bool EpollMgr::DelSocket(NetSocket* netSocket)
{
	return m_epollCtrl.Del(netSocket->GetSockFd());
}
