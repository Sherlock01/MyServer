#include "net_socket.h"


NetSocket::NetSocket(SocketType type)
	:m_sockFd(-1)
	,m_type(type)
	,m_state(SOCKET_STATE_INVALID)
{

}

NetSocket::~NetSocket()
{

}

void NetSocket::Init(int sockFd)
{
	m_sockFd = sockFd;
}

void NetSocket::UnInit()
{
	m_sockFd = -1;
}
