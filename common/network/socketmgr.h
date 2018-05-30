#ifndef __SOCKETMGR_H__
#define __SOCKETMGR_H__

#include "net_def.h"
#include "net_socket.h"

#include <unordered_map>
#include <vector>

class NetSocket;
class ListenSocket;
class ConnectSocket;

class SocketMgr
{
public:
	SocketMgr();
	~SocketMgr();

	bool Init(uint32_t connTmpMax);
	void UnInit();

	ListenSocket* AllocListenSocket(HNetReqInfo& req);
	ConnectSocket* AllocConnectSocket(HNetReqInfo& req);

	NetSocket* GetSocket(SocketKeyID keyID);
	void FreeSocket(SocketKeyID keyID);

private:
	//正在使用
	std::unordered_map<SocketKeyID, NetSocket*> m_sockets;
	//缓存
	std::vector<ConnectSocket*> m_connectTmp;
	uint32_t m_connTmpMax;
};

#endif

