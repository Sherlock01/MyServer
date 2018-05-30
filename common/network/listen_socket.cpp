#include "listen_socket.h"

ListenSocket::ListenSocket()
	:NetSocket(SOCKET_TYPE_LISTEN)
	,m_port(0)
{

}

ListenSocket::~ListenSocket()
{

}

void ListenSocket::InitListen(int sockFd, uint16_t port)
{
	Init(sockFd);
	m_port = port;
}

void ListenSocket::UnInit()
{
	m_port = 0;
	NetSocket::UnInit();
}
