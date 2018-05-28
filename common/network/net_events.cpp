#include "net_events.h"

#include "ptr_pipe.h"
#include "mem_buffer.h"
#include "net_def.h"

NetEvents::NetEvents()
{

}

NetEvents::~NetEvents()
{

}

void NetEvents::Update()
{
	auto logic2net = PipeMgr()->Logic2Net();
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

	return HNET::FUNC_SUCCESS;
}

int NetEvents::ProConnect(HNetReqInfo& info)
{

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
