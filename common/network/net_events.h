#ifndef __NET_EVENT_H__
#define __NET_EVENT_H__

class PtrPipeMgr;

class NetEvents
{
public:
	NetEvents();
	~NetEvents();

	void Update();

	int ProListen(HNetReqInfo& info);
	int ProConnect(HNetReqInfo& info);	
	int ProDisConnect(HNetReqInfo& info);
	int ProSendData(HNetReqInfo& info);

private:
	inline PtrPipeMgr* PipeMgr() { return PtrPipeMgr::Instance(); };

#endif



