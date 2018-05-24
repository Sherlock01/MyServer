#include "net_logic.h"


NetHandler::NetHandler()
{

}

NetHandler::~NetHandler()
{

}

void NetHandler::Update()
{
	auto logic2net = PipeMgr()->Logic2Net();

	logic2net->UpdateSend();

	void* ptr = NULL;
	while ((ptr = logic2net->ReadBack()))
	{
		m_memPool.GiveBack((MemPool*)ptr);
	}
}

int NetHandler::ReqListen(uint16_t port)
{
	auto ptr = m_memPool.Borrow(sizeof(HNetReqInfo));
	if (NULL == ptr)
	{
		return -11;
	}
	HNetReqInfo* req = (HNetReqInfo*)(ptr->BufferHead());
	req->type = HNRT_LISTEN;
	req->info.listen.port = port;
	return PipeMgr()->Logic2Net()->WriteSend(ptr);
}

int NetHandler::ReqConnect(uint32_t addr, uint16_t port)
{
	auto ptr = m_memPool.Borrow(sizeof(HNetReqInfo));
	if (NULL == ptr)
	{
		return -11;
	}
	HNetReqInfo* req = (HNetReqInfo*)(ptr->BufferHead());
	req->type = HNRT_CONNECT;
	req->info.connect.addr = addr;
	req->info.connect.port = port;
	return PipeMgr()->Logic2Net()->WriteSend(G)
}

int NetHandler::ReqDisConnect(ConnID connID)
{
	auto ptr = m_memPool.Borrow(sizeof(HNetReqInfo));
	if (NULL == ptr)
	{
		return -11;
	}
	HNetReqInfo* req = (HNetReqInfo*)(ptr->BufferHead());
	req->type = HNRT_DISCONNECT;
	req->info.disconnect.connID = connID;
	return PipeMgr()->Logic2Net()->WriteSend(ptr);
}

int NetHandler::ReqSendData(char* data, uint16_t len)
{
	auto ptr = m_memPool.Borrow(sizeof(HNetReqInfo) + len);
	if (NULL == ptr)
	{
		return -11;
	}
	HNetReqInfo* req = (HNetReqInfo*)(ptr->BufferHead());
	req->type = HNRT_SENDDATA;
	req->info->senddata.len = len;
	memcpy(req->info->senddata.data, data, len);
	return PipeMgr()->Logic2Net()->WriteSend(ptr);
}

PtrPipeMgr* NetHandler::PipeMgr()
{
	return PtrPipeMgr::Instance();
}

