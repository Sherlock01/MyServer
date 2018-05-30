#include "net_events.h"

#include "ptr_pipe.h"
#include "mem_buffer.h"
#include "net_def.h"
#include "net_thread.h"
#include "socketmgr.h"

NetEvents::NetEvents()
	:m_netThread(NULL)
{

}

NetEvents::~NetEvents()
{

}

bool NetEvents::Init(NetThread* netThread)
{
	m_netThread = netThread;
}
void NetEvents::UnInit()
{
	m_netThread = NULL;
}

void NetEvents::Update()
{
	auto logic2net = GetNetThread()->GetPipeMgr().Logic2Net();
	void* ptr = NULL;
	while (ptr = logic2net->ReadSend())
	{
		HNetReqInfo* req = (HNetReqInfo*)(ptr);
		int ret = HNET::FUNC_SUCCESS;
		switch (req->type)
		{
		case HNRT_LISTEN:
			{
				ret = ProListen(*req);
			}
			break;
		case HNRT_CONNECT:
			{
				ret = ProConnect(*req);
			}
			break;
		case HNRT_DISCONNECT:
			{
				ret = ProDisConnect(*req);
			}
			break;
		case HNRT_SENDDATA:
			{
				req = ProSendData(*req);
			}
			break;
		default:
			break;
		}
		if (HNET::FUNC_SUCCESS != ret)
		{
			//TODO
		}
	}
}

int NetEvents::ProListen(HNetReqInfo& info)
{
	ListenSocket* netSocket = GetNetThread()->GetSocketMgr()->AllocListenSocket(info);
	if (NULL == netSocket)
	{
		return HNET::FUNC_FAILED;
	}

	if (!GetNetThread()->GetEpollMgr()->AddListenSocket(netSocket)
	{
		return HNET::FUNC_FAILED;
	}
	
	return HNET::FUNC_SUCCESS;
}

int NetEvents::ProConnect(HNetReqInfo& info)
{
	ConnectSocket* netSocket = ConnectSocket* netSocket = GetNetThread()->GetSocketMgr()->AllocConnectSocket(info);
	if (NULL == netSocket)
	{
		return HNET::FUNC_FAILED;
	}

	if (!GetNetThread()->GetEpollMgr()->AddConnectSocket(netSocket))
	{
		return HNET::FUNC_FAILED;
	}
	
	return HNET::FUNC_SUCCESS;
}

int NetEvents::ProDisConnect(HNetReqInfo& info)
{

	return HNET::FUNC_SUCCESS;
}

int NetEvents::ProSendData(HNetReqInfo& info)
{
	return HNET::FUNC_SUCCESS;
}
