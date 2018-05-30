#ifndef __LISTEN_SOCKET_H__
#define __LISTEN_SOCKET_H__

#include "net_socket.h"

class ListenSocket : public NetSocket
{
public:
	ListenSocket();
	~ListenSocket();

	void InitListen(int sockFd, uint16_t port);
	virtual void UnInit();

	inline uint16_t GetPort() { return m_port; }	

private:
	uint16_t m_port;
};

#endif

