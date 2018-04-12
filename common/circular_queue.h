#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <stdint.h>

class CircularQueue
{
public:
	CircularQueue(uint32_t size);
	~CircularQueue();

	bool Init(uint32_t size);
	void UnInit();

	bool Write(char* str, uint32_t len);
	bool Read(char* str, uint32_t len);

private:
	uint32_t Used();
	uint32_t Left();

	inline char* HeadPtr() { return m_buffer + m_head; }
	inline char* TailPtr() { return m_buffer + m_tail; }

private:
	char* m_buffer;
	uint32_t m_size;
	uint32_t volatile m_head;
	uint32_t volatile m_tail;
};

#endif
