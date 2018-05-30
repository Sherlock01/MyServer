#ifndef __CONNECT_LINK_H__
#define __CONNECT_LINK_H__

#include "baselink.h"

class ConnectLinkOne : public BaseLink
{
public:
	ConnectLinkOne();
	~ConnectLinkOne();

	virtual LinkType GetLinkType() { return LINK_TYPE_CONNECT_ONE; }
	virtual bool IsConnectType() { return true; }

	void Init(const LinkConfig& config);

	virtual void OnConnected(LinkConnID connID);
	virtual void OnClose(LinkConnID connID);

private:
	LinkConnID m_connID;
};

class ConnectLinkLine : public BaseLink
{
public:
	ConnectLinkLine();
	~ConnectLinkLine();

	virtual LinkType GetLinkType() { return LINK_TYPE_CONNECT_LINE; }
	virtual bool IsConnectType() { return true; }

	void Init(const std::vector<LinkConfig>& config);

	virtual void OnConnected(LinkConnID connID);
	virtual void OnClose(LinkConnID connID);

private:
	std::unordered_set<LinkConnID> m_connIDs;
};

#endif