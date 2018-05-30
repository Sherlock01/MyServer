#ifndef __NET_SOCKET_H__
#define __NET_SOCKET_H__

#include <cstdint>

enum SocketType
{
	SOCKET_TYPE_LISTEN,
	SOCKET_TYPE_CONNECT,
};

enum SocketState
{
	SOCKET_STATE_INVALID,
	SOCKET_STATE_LISTENING,
	SOCKET_STATE_CONNECTING,
	SOCKET_STATE_ESTABLISHED,
};

typedef int SocketKeyID;

class NetSocket
{
public:
	NetSocket(SocketType type);
	virtual ~NetSocket();

	void Init(int sockFd);
	virtual void UnInit();

	inline SocketKeyID KeyID() { return m_sockFd; }
	inline int GetSockFd() { return m_sockFd; }
	inline void SetSockFd(int fd} { m_sockFd = fd; }

	inline SocketType GetType() { return m_type; }

	inline SocketState GetState() { return m_state; }
	inline void SetState(SocketState state) { m_state = state; }

private:
	int m_sockFd;
	SocketType m_type;
	SocketState m_state;
};

#endif

