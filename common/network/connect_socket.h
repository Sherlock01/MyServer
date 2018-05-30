#ifndef __CONNECT_SOCKET_H__
#define __CONNECT_SOCKET_H__

#include "net_socket.h"

class ConnectSocket : public NetSocket
{
public:
	ConnectSocket();
	~ConnectSocket();

	void InitConnect(int sockFd, uint32_t ip, uint16_t port);
	virtual void UnInit();

	inline uint32_t GetIP() { return m_ip; }
	inline uint32_t GetPort() { return m_port; }

private:
	uint32_t m_ip;
	uint16_t m_port;
};

#endif

