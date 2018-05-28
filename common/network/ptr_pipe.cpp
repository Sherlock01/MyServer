#include "ptr_pipe.h"

PtrOnewayPipe::PtrOnewayPipe(uint32_t queSize, uint32_t tmpSize)
	:m_ptrQueue(queSize)
	,m_tmpMaxSize(tmpSize)
{
	
}

PtrOnewayPipe::~PtrOnewayPipe()
{
	//不处理临时保存的指针所指向的内存
}

int PtrOnewayPipe::Write(void* ptr)
{
	if (!m_ptrTmp.empty())
	{
		if (m_ptrTmp.size() >= m_tmpMaxSize)
		{
			return HNET::FUNC_F_ONEWAY_PTRTMPFULL;
		}
		m_ptrTmp.push_back(ptr);
		return HNET::FUNC_S_ONEWAY_INTO_PTRTMP;
	}
	if (!m_ptrQueue.Write(ptr))
	{
		m_ptrTmp.push_back(ptr);
		return HNET::FUNC_S_ONEWAY_INTO_PTRTMP;
	}
	return HNET::FUNC_SUCCESS;
}

void PtrOnewayPipe::Update()
{
	for (auto it = m_ptrTmp.begin(); it != m_ptrTmp.end();)
	{
		if (m_ptrQueue.Write(*it))
		{
			m_ptrTmp.erase(it++);
		}
		else
		{
			return;
		}
	}
}

PtrTwowayPipe::PtrTwowayPipe(uint32_t sendQueSize, uint32_t sendTmpSize, uint32_t backQueSize, uint32_t backTmpSize)
	:m_sendPipe(sendQueSize, sendTmpSize)
	,m_backPipe(backQueSize, backTmpSize)
{

}

PtrTwowayPipe::~PtrTwowayPipe()
{

}


PtrPipeMgr::PtrPipeMgr()
	:m_logic2net(NULL)
	,m_net2logic(NULL)
{

}

PtrPipeMgr::~PtrPipeMgr()
{

}

void PtrPipeMgr::Init()
{
	m_logic2net = new PtrTwowayPipe(10, 100, 10, 100);
	m_net2logic = new PtrTwowayPipe(10, 100, 10, 100);
}

void PtrPipeMgr::UnInit()
{
	delete m_logic2net;
	m_logic2net = NULL;
	delete m_net2logic;
	m_net2logic = NULL;
}
