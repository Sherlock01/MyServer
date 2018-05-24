#ifndef __PTR_PIPE_H__
#define __PTR_PIPE_H__

#include "ptr_circular_queue.h"
#include "singleton.h"

#include <list>

#include <cstdint>

class PtrOnewayPipe
{
public:
	PtrOnewayPipe(uint32_t queSize, uint32_t tmpSize);
	~PtrOnewayPipe();

	int Write(void* ptr);
	void Update();

	inline void* Read() { return m_ptrQueue.Read(); }

private:
	PtrCircularQueue m_ptrQueue;

	std::list<void*> m_ptrTmp;
	uint32_t m_tmpMaxSize;
};

class PtrTwowayPipe
{
public:
	PtrTwowayPipe(uint32_t sendQueSize, uint32_t sendTmpSize, uint32_t backQueSize, uint32_t backTmpSize);
	~PtrTwowayPipe();

	inline int WriteSend(void* ptr) { return m_sendPipe.Write(ptr); }
	inline void* ReadBack() { return m_backPipe.Read(); }
	inline void UpdateSend() { m_sendPipe.Update() };

	inline int WriteBack(void* ptr) { return m_backPipe.Write(ptr); }
	inline void* ReadSend() { return m_sendPipe.Read(); }
	inline void UpdateBack() { m_backPipe.Update(); }

private:
	PtrOnewayPipe m_sendPipe;
	PtrOnewayPipe m_backPipe;
};

class PtrPipeMgr : public Singleton<PtrPipeMgr>
{
public:
	PtrPipeMgr();
	~PtrPipeMgr();

	void Init();
	void UnInit();

	PtrTwowayPipe* Logic2Net() { return m_logic2net; }
	PtrTwowayPipe* Net2Logic() { return m_net2logic; }

private:
	PtrTwowayPipe* m_logic2net;
	PtrTwowayPipe* m_net2logic;
};

#endif

