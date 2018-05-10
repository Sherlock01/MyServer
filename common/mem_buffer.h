#ifndef  __MEM_BUFFER_H__
#define  __MEM_BUFFER_H__

#include <stdint.h>
#include <stddef.h>

class MemBuffer
{
public:
	MemBuffer(uint32_t capacity);
	~MemBuffer();

	inline bool CanUse() { return NULL != m_buffer; }
	inline uint32_t Size() { return m_tail - m_head; }
	inline uint32_t Capacity() { return m_capacity; }

	bool Write(const char* str, uint32_t len);
	bool ReadOnly(char* str, uint32_t len);
	bool ReadAndRemove(char* str, uint32_t len);	

	void Reset();

private:
	bool Init(uint32_t capacity);
	void UnInit();

private:
	char* m_buffer;
	uint32_t m_capacity;
	uint32_t m_head;
	uint32_t m_tail;
};

#endif
