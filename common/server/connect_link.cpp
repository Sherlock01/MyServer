#include "connect_link.h" 

ConnectLinkOne::ConnectLinkOne()
	:m_connID(INVAILDCONNID)
{

}

ConnectLinkOne::~ConnectLinkOne()
{

}

void ConnectLinkOne::OnConnected(LinkConnID connID)
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

void ConnectLinkOne::OnClose(LinkConnID connID)
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

void ConnectLinkOne::Init(const LinkConfig& config)
{
	SetLinkConfig(config);
}


ConnectLinkLine::ConnectLinkLine()
{

}

ConnectLinkLine::~ConnectLinkLine()
{

}

void ConnectLinkLine::Init(const std::vector<LinkConfig>& config)
{
	SetLinkConfig(config);
}

void ConnectLinkLine::OnConnected(LinkConnID connID)
{
	auto ret = m_connIDs.insert(connID);
	if (!ret.second)
	{
		;//TODO
	}
}

void ConnectLinkLine::OnClose(LinkConnID connID)
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
