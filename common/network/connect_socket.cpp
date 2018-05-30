#include "connect_socket.h"


ConnectSocket::ConnectSocket()
	:NetSocket(SOCKET_TYPE_CONNECT)
	,m_ip(0)
	,m_port(0)
{

}

ConnectSocket::~ConnectSocket()
{

}

void ConnectSocket::InitConnect(int sockFd, uint32_t ip, uint16_t port)
{
	Init(sockFd);
	m_ip = ip;
	m_port = port;
}

void ConnectSocket::UnInit()
{
	m_ip = 0;
	m_port = 0;
	NetSocket::UnInit();
}
