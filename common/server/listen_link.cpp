#include "listen_link.h"

ListenLinkOne::ListenLinkOne()
{

}

ListenLinkOne::~ListenLinkOne()
{

}

void ListenLinkOne::OnConnected(LinkConnID connID)
{
	if (INVAILDCONNID == m_connID)
	{
		m_connID = connID;
	}
	else
	{
		;//TODO
	}
}

void ListenLinkOne::OnClose(LinkConnID connID)
{
	if (connID == m_connID)
	{
		m_connID = INVAILDCONNID;
	}
	else
	{
		;//TODO
	}
}

ListenLinkLine::ListenLinkLine()
{

}

ListenLinkLine::~ListenLinkLine()
{

}

void ListenLinkLine::OnConnected(LinkConnID connID)
{
	auto ret = m_connIDs.insert(connID);
	if (!ret.second)
	{
		;//TODO
	}
}

void ListenLinkLine::OnClose(LinkConnID connID)
{
	auto it = m_connIDs.find(connID);
	if (it != m_connIDs.end())
	{
		m_connIDs.erase(connID);
	}
	else
	{
		;//TODO
	}
}
