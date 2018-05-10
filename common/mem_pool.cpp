#include "mem_pool.h"

#include <cstdio>

uint32_t CloserTo2Pow(uint32_t k)
{
	//未做越界检测
	uint32_t ret = CAPACITY_INTERVAL_MULTIPLE;
	while (ret < k)
	{
		ret <<= CAPACITY_INTERVAL_2_EXP;
	}
	return ret;
}


MemList::MemList(uint32_t capacity)
	:m_capacity(capacity)
	,m_notEmptyTime(0)
	,m_allCount(0)
{

}

MemList::~MemList()
{
	for (size_t i = 0; i < m_mems.size(); ++i)
	{
		delete m_mems[i];
	}
	m_mems.clear();
}

MemBuffer* MemList::Borrow()
{
	if (m_mems.empty())
	{
		NewOne();
	}
	MemBuffer* buffer = m_mems.empty()? NULL: m_mems.back();
	if (NULL == buffer)
	{
		return NULL;
	}
	m_mems.pop_back();
	if (m_mems.empty())
	{
		m_notEmptyTime = 0;
	}
	return buffer;
}

void MemList::GiveBack(MemBuffer* buffer)
{
	if (NULL == buffer)
	{
		printf("give back buffer = null\n");
		return;
	}
	m_mems.push_back(buffer);
	if (0 == m_notEmptyTime)
	{
		m_notEmptyTime = time(NULL);
	}
}

void MemList::CheckFree(time_t now)
{
	if (0 == m_notEmptyTime || m_notEmptyTime + BUFFER_USELESS_FREE_TIME >= now)
	{
		return;
	}
	DelOne();
	if (m_mems.empty())
	{
		m_notEmptyTime = 0;
	}
	else
	{
		m_notEmptyTime = now;
	}
}

void MemList::DelOne()
{
	if (m_mems.empty())
	{
		printf("del one empty\n");
		return;
	}
	MemBuffer* buffer = m_mems.back();
	m_mems.pop_back();
	delete buffer;
	buffer = NULL;
	-- m_allCount;
}

MemBuffer* MemList::NewOne()
{
	MemBuffer* buffer = new MemBuffer(m_capacity);
	if (NULL == buffer)
	{
		printf("new one membufer = null\n");
		return NULL;
	}
	if (!buffer->CanUse())
	{
		delete buffer;
		return NULL;
	}
	++ m_allCount;
	m_mems.push_back(buffer);
	return buffer;
}

MemPool::MemPool()
{

}

MemPool::~MemPool()
{

}

void MemPool::Update(time_t now)
{
	CheckFree(now);
}

MemBuffer* MemPool::Borrow(uint32_t size)
{
	uint32_t capacity = GetSuitbleSize(size);
	if (capacity > CAPACITY_MAX)
	{
		printf("borrow buffer capacity too large capacity = %d\n", capacity);
		return NULL;
	}
	auto it = m_pool.find(capacity);
	if (it == m_pool.end())
	{
		MemList* list = new MemList(capacity);
		if (NULL == list)
		{
			return NULL;
		}
		m_pool[capacity] = list;
	}
	return m_pool[capacity]->Borrow();
}

void MemPool::GiveBack(MemBuffer* buffer)
{
	if (NULL == buffer)
	{
		printf("give back buffer = null\n");
		return;
	}
	uint32_t capacity = buffer->Capacity();
	auto it = m_pool.find(capacity);
	if (it == m_pool.end())//理论上不会出现
	{
		printf("give back find memlist failed\n");
		MemList* list = new MemList(capacity);
		if (NULL == list)
		{
			return ;
		}
		m_pool[capacity] = list;
	}

	m_pool[capacity]->GiveBack(buffer);
}

void MemPool::CheckFree(time_t now)
{
	for (auto it = m_pool.begin(); it != m_pool.end(); )
	{
		MemList* list = it->second;
		list->CheckFree(now);
		if (0 == list->Size() && list->AllCount() <= 0)
		{
			m_pool.erase(it++);
			delete list;
			list = NULL;
		}
		else
		{
			it++;
		}
	}
}

uint32_t MemPool::GetSuitbleSize(uint32_t size)
{
	//策略待优化 TODO
	return CloserTo2Pow(size);
}
