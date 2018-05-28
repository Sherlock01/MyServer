#include "epollmgr.h"


EpollCtrl::EpollCtrl()
{

}

EpollCtrl::~EpollCtrl()
{

}

bool EpollCtrl::Init()
{
	return true;
}

void EpollCtrl::UnInit()
{

}

EpollMgr::EpollMgr()
{

}

EpollMgr::~EpollMgr()
{

}

bool EpollMgr::Init()
{
	if (!m_epollCtrl.Init())
	{
		return false;
	}
	return true;
}

void EpollMgr::UnInit()
{

}

void EpollMgr::Update()
{

}
