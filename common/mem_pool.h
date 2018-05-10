#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#include "mem_buffer.h"

#include <vector>
#include <cmath>
#include <ctime>
#include <unordered_map>

#define CAPACITY_INTERVAL_2_EXP 1
#define CAPACITY_INTERVAL_MULTIPLE 2 // (pow(2, CAPACITY_INTERVAL_2_EXP)
#define CAPACITY_MAX 4096 //要跟协议大小相关联

#define BUFFER_USELESS_FREE_TIME 60 //(second)

uint32_t CloserTo2Pow(uint32_t k);

class MemList
{
public:
	MemList(uint32_t capacity);
	~MemList();

	inline uint32_t Size() { return m_mems.size(); }
	inline uint32_t AllCount() { return m_allCount; }

	MemBuffer* Borrow();
	void GiveBack(MemBuffer* buffer);

	void CheckFree(time_t now);

private:
	void DelOne();
	MemBuffer* NewOne();

private:
	uint32_t m_capacity;
	std::vector<MemBuffer*> m_mems;

	time_t m_notEmptyTime;//记录开始非空的时间 
	int32_t m_allCount;//拥有的加上借出的
};

class MemPool
{
public:
	MemPool();
	~MemPool();

	void Update(time_t now);

	MemBuffer* Borrow(uint32_t size);
	void GiveBack(MemBuffer* buffer);

private:
	void CheckFree(time_t now);
	uint32_t GetSuitbleSize(uint32_t size);

private:
	// <capacity, memlist>
	std::unordered_map<uint32_t, MemList*> m_pool;	
};

#endif