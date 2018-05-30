#ifndef __BASELINK_H__
#define __BASELINK_H__

#include <cstdint>
#include <vector>
#include <unordered_set>

enum LinkState
{
	LINK_STATE_INVAILD,

	LINK_STATE_LISTEN_WAIT,
	LINK_STATE_LISTEN_FAIL,
	LINK_STATE_LISTEN_SUCCESS,

	LINK_STATE_CONNECT_WAIT,
	LINK_STATE_CONNECT_FAIL,
	LINK_STATE_CONNECT_SUCCESS,
};

enum LinkType
{
	LINK_TYPE_LISTEN_ONE,
	LINK_TYPE_LISTEN_LINE,
	LINK_TYPE_CONNECT_ONE,
	LINK_TYPE_CONNECT_LINE,
};

struct LinkConfig
{
	uint32_t ip;	
	uint16_t port;
	uint32_t recvBufferSize;
	uint32_t sendBufferSize;
};

typedef int32_t LinkConnID;
#define INVAILDCONNID -1

class BaseLink
{
public:
	BaseLink();
	virtual ~BaseLink();

	virtual void OnConnected(LinkConnID connID) = 0;
	virtual void OnClose(LinkConnID connID) = 0;

	virtual LinkType GetLinkType() = 0;
	virtual bool IsListenType() { return false; }
	virtual bool IsConnectType() { return false; }

	inline void SetLinkConfig(const LinkConfig& config) { m_configs.push_back(config); }
	inline void SetLinkConfig(const std::vector<LinkConfig>& configs) { m_configs = configs; }
	inline const std::vector<LinkConfig>& GetConfigs() { return m_configs; } 

	inline LinkState GetLinkState() { return m_state; }
	inline void SetLinkState(LinkState state) { m_state = state; }

private:
	LinkState m_state;
	std::vector<LinkConfig> m_configs;
};

#endif

