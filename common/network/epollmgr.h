#ifndef __EPOLLMGR_H__
#define __EPOLLMGR_H__

class ListenSocket;
class ConnectSocket;

class EpollCtrl
{
public:
	EpollCtrl();
	~EpollCtrl();

	bool Init(int maxCount);
	void UnInit();

	bool Add(int sock, uint32_t, void* ptr);
	bool Del(int sock);
	int Wait(int msec);

	struct epoll_event* GetEvent(int index);

private:	
	struct epoll_event* m_events;
	int m_maxCount;
	int m_epollFd;
};

class EpollMgr
{
public:
	EpollMgr();
	~EpollMgr();

	bool Init();
	void UnInit();

	void Update();

	bool AddListenSocket(ListenSocket* netSocket);
	bool AddConnectSocket(ConnectSocket* netSocket);
	bool DelSocket(NetSocket* netSocket);

	EpollCtrl& GetEpollCtrl() { return m_epollCtrl; }

private:
	EpollCtrl m_epollCtrl;
};

#endif

