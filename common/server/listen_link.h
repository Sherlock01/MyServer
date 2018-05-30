#ifndef __LISTEN_LINK_H__
#define __LISTEN_LINK_H__

#include "baselink.h"

class ListenLinkOne : public BaseLink
{
public:
	ListenLinkOne();
	~ListenLinkOne();

	virtual LinkType GetLinkType() { return LINK_TYPE_LISTEN_ONE; }
	virtual bool IsListenType() { return true; }

	virtual void OnConnected(LinkConnID connID);
	virtual void OnClose(LinkConnID connID);

private:
	LinkConnID m_connID;
};

class ListenLinkLine: public BaseLink
{
public:
	ListenLinkLine();
	~ListenLinkLine();

	virtual LinkType GetLinkType() { return LINK_TYPE_LISTEN_LINE; }
	virtual bool IsListenType() { return true; }

	virtual void OnConnected(LinkConnID connID);
	virtual void OnClose(LinkConnID connID);

private:
	std::unordered_set<LinkConnID> m_connIDs;
};

#endif