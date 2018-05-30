#ifndef __NET_EVENT_H__
#define __NET_EVENT_H__

class NetThread;

class NetEvents
{
public:
	NetEvents();
	~NetEvents();

	bool Init(NetThread* netThread);
	void UnInit();

	void Update();

	int ProListen(HNetReqInfo& info);
	int ProConnect(HNetReqInfo& info);	
	int ProDisConnect(HNetReqInfo& info);
	int ProSendData(HNetReqInfo& info);

private:
	inline NetThread* GetNetThread() { return m_netThread; }

private:
	NetThread* m_netThread;
}

#endif



