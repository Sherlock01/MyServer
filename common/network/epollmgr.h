#ifndef __EPOLLMGR_H__
#define __EPOLLMGR_H__

class EpollCtrl
{
public:
	EpollCtrl();
	~EpollCtrl();

	bool Init();
	void UnInit();

private:	

};

class EpollMgr
{
public:
	EpollMgr();
	~EpollMgr();

	bool Init();
	void UnInit();

	void Update();

	EpollCtrl& GetEpollCtrl() { return m_epollCtrl; }

private:
	EpollCtrl m_epollCtrl;
};

#endif

