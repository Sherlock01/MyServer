#include "linkmgr.h"
#include "connect_link.h"
#include "listen_link.h"

LinkMgr::LinkMgr()
	:m_state(LINKMGR_INIT_INVAILD)
{

}

LinkMgr::LinkMgr()
{

}

LinkMgr::~LinkMgr()
{

}

void LinkMgr::Update()
{
	switch(m_state)
	{
	case LINKMGR_INIT_LISTEN:
		{
			CheckListenInit();
		}
		break;
	case LINKMGR_INIT_CONNECT:
		{
			CheckConnectInit();
		}
		break;
	default:
		break;
	}
}

void LinkMgr::OnListenFailed()
{

}

void LinkMgr::OnConnectFailed()
{

}

void LinkMgr::CheckListenInit()
{
	bool succeed = true;
	bool failed = false;
	for (auto it = m_listenLinks.begin(); it != m_listenLinks.end(); ++it)
	{
		BaseLink* link = (*it);
		LinkState state = link->GetLinkState();	
		if (LINK_STATE_LISTEN_SUCCESS != state)	
		{
			succeed = false;
		}
		if (LINK_STATE_LISTEN_FAIL == state)
		{
			failed = true;
			break;
		}
		if (LINK_STATE_INVAILD == state)
		{
			;//TODO
			link->SetLinkState(LINK_STATE_LISTEN_WAIT);
		}
		
	}
	if (failed)
	{
		SetState(LINKMGR_INIT_LISTEN_FAIL);
		return;
	}
	if (succeed)
	{
		SetState(LINKMGR_INIT_CONNECT);
	}
}

void LinkMgr::CheckConnectInit()
{
	bool succeed = true;
	for (auto it = m_connectLinks.begin(); it != m_connectLinks.end(); ++it)
	{
		BaseLink* link = (*it);
		LinkState state = link->GetLinkState();	
		if (LINK_STATE_CONNECT_SUCCESS != state)
		{
			succeed = false;	
		}
		if (LINK_STATE_INVAILD == state || LINK_STATE_CONNECT_FAIL == state)
		{
			;//TODO
			link->SetLinkState(LINK_STATE_CONNECT_WAIT);
		}
	}

	if (succeed)
	{
		SetState(LINKMGR_INIT_SUCCESS);
	}
}

void LinkMgr::Register(BaseLink* link)
{
	if (link->IsListenType())	
	{
		auto ret = m_listenLinks.insert(link);
		if (!ret.second)
		{
			;//TODO
		}
	}
	else if(link->IsConnectType())
	{
		auto ret = m_connectLinks.insert(link);
		if (!ret.second)
		{
			;//TODO
		}
	}
}

void LinkMgr::UnRegister(BaseLink* link)
{
	if (link->IsListenType())	
	{
		m_listenLinks.erase(link);
	}
	else if(link->IsConnectType())
	{
		m_connectLinks.emplace(link);
	}
}

