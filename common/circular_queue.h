#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <stdint.h>

class CircularQueue
{
public:
	CircularQueue(uint32_t size);
	virtual ~CircularQueue();

	bool Init(uint32_t size);
	void UnInit();

	bool Write(const char* str, uint32_t len);
	bool Read(char* str, uint32_t len);

protected:
	char* m_buffer;
	uint32_t m_size;
	uint32_t volatile m_head;
	uint32_t volatile m_tail;
};

#endif
