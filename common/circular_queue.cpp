#include "circular_queue.h"

#include <cstring>

CircularQueue::CircularQueue(uint32_t size)
	:m_buffer(NULL)
	,m_size(0)
	,m_head(0)
	,m_tail(0)
{
	Init(size);
}

CircularQueue::~CircularQueue()
{
	UnInit();
}

bool CircularQueue::Init(uint32_t size)
{
	m_buffer = new char[size];
	if (NULL == m_buffer)
	{
		return false;
	}
	m_size = size;
	m_head = 0;
	m_tail = 0;

	return true;
}

void CircularQueue::UnInit()
{
	delete[] m_buffer;
	m_buffer = NULL;
	m_size = 0;
	m_head = 0;
	m_tail = 0;
}


bool CircularQueue::Write(const char* str, uint32_t len)
{
	if (NULL == str || 0 == len)
	{
		return false;
	}
	if (Left() < len)
	{
		return false;
	}

	if (m_tail + len < m_size)		
	{
		memcpy(TailPtr(), str, len);
		m_tail += len;
	}
	else
	{
		uint32_t seg1 = m_size - m_tail;
		uint32_t seg2 = len - seg1;
		memcpy(TailPtr(), str, seg1);
		memcpy(m_buffer, str + seg1, seg2);
		m_tail = seg2;
	}

	return true;
}

bool CircularQueue::Read(char* str, uint32_t len)
{
	if (NULL == str || 0 == len)
	{
		return false;
	}
	if (Used() < len)
	{
		return false;
	}
	if (m_tail >= m_head)
	{
		memcpy(str, HeadPtr(), len);
		m_head += len;
	}
	else
	{
		uint32_t seg1 = len - m_tail;
		uint32_t seg2 = len - seg1;
		memcpy(str, HeadPtr(), seg1);
		memcpy(str + seg1, m_buffer, seg2);
		m_head = seg2;
	}
	return true;
}

uint32_t CircularQueue::Used()
{
	if (m_tail >= m_head)
	{
		return m_tail - m_head;
	}
	else
	{
		return m_tail + m_size - m_head;
	}
}

uint32_t CircularQueue::Left()
{
	return m_size - Used() - 1;
}

