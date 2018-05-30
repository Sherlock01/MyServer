#ifndef __LINKMGR_H__
#define __LINKMGR_H__

#include "singleton.h"
#include "net_handler.h"

#include <vector>
#include <unordered_set>

class BaseLink;

enum LinkMgrState
{
	LINKMGR_INIT_INVAILD,
	LINKMGR_INIT_LISTEN,
	LINKMGR_INIT_CONNECT,
	LINKMGR_INIT_SUCCESS,
	LINKMGR_INIT_LISTEN_FAIL,
	//LINKMGR_INIT_CONNECT_FAIL,
};

class LinkMgr : public Singleton<LinkMgr>
{
public:
	LinkMgr();
	~LinkMgr();

	void Update();

	inline LinkMgrState GetState() { return m_state; }
	inline LinkMgrState SetState(LinkMgrState state) { return m_state = state; }

	void Register(BaseLink* link);
	void UnRegister(BaseLink* link);

	void OnListenFailed();
	void OnConnectFailed();

private:
	void CheckListenInit();
	void CheckConnectInit();

private:
	LinkMgrState m_state;
	std::unordered_set<BaseLink*> m_listenLinks;
	std::unordered_set<BaseLink*> m_connectLinks;

	NetHandler m_netHandler;
};

#endif



