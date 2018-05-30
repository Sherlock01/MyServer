#include "socketmgr.h"

#include "listen_socket.h"
#include "connect_socket.h"

SocketMgr::SocketMgr()
{

}

SocketMgr::~SocketMgr()
{

}

bool SocketMgr::Init(uint32_t connTmpMax)
{
	m_connTmpMax = connTmpMax;
}

void SocketMgr::UnInit()
{
	for (auto it = m_sockets.begin(); it != m_sockets.end(); ++it)
	{
		delete it->second;
	}
	m_sockets.clear();
	
	for (size_t i = 0; i < m_connectTmp.size(); ++i)
	{
		delete m_connectTmp[i];
	}
	m_connectTmp.clear();
}

ListenSocket* SocketMgr::AllocListenSocket(HNetReqInfo& req)
{
	ListenSocket* netSocket = new ListenSocket();			
	
	netSocket->Init(1);

	m_sockets.insert(std::make_pair(netSocket->KeyID(), netSocket));

	return netSocket;
}

ConnectSocket* SocketMgr::AllocConnectSocket(HNetReqInfo& req)
{
	ConnectSocket* netSocket = NULL;
	if (!m_connectTmp.empty())
	{
		netSocket = m_connectTmp.back();
		m_connectTmp.pop_back();
		return netSocket;
	}
	netSocket = new ConnectSocket();			
	
	netSocket->Init(1);

	m_sockets.insert(std::make_pair(netSocket->KeyID(), netSocket));

	return netSocket;
}

void SocketMgr::FreeSocket(int keyID)
{
	NetSocket* netSocket = GetSocket(keyID);
	if (NULL == netSocket)
	{
		return;
	}
	m_sockets.erase(keyID);

	netSocket->UnInit();

	if (netSocket->GetType() == SOCKET_TYPE_CONNECT && m_connectTmp.size() < m_connTmpMax)
	{
		m_connectTmp.push_back((ConnectSocket*)netSocket);
		return;
	}

	delete netSocket;
	netSocket = NULL;
}

NetSocket* SocketMgr::GetSocket(SocketKeyID keyID)
{
	auto it = m_sockets.find(keyID);
	if (it != m_sockets.end())
	{
		return it->second;
	}
	return NULL;
}
