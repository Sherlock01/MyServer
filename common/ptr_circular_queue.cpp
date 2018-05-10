#include "ptr_circular_queue.h"

#include <stddef.h>

PtrCircularQueue::PtrCircularQueue(uint32_t size)
    :m_buffer(NULL)
     ,m_size(0)
     ,m_head(0)
     ,m_tail(0)
{
    Init(size); 
}

PtrCircularQueue::~PtrCircularQueue()
{
    UnInit();
}

bool PtrCircularQueue::Init(uint32_t size)
{
    m_buffer = new void*[size];
    if (NULL == m_buffer)
    {
        return false;
    }
    m_size = size;
    m_head = 0;
    m_tail = 0;

    return true;
}

void PtrCircularQueue::UnInit()
{
    delete[] m_buffer;
    m_buffer = NULL;
    m_size = 0;
    m_head = 0;
    m_tail = 0;
}

bool PtrCircularQueue::Write(void* ptr)
{
    if (NULL == ptr)
    {
        return false;
    }
    uint32_t tmphead = m_head;
    if ((m_tail + 1) % m_size == tmphead)
    {
        return false;
    }

    m_buffer[m_tail] = ptr;
    m_tail = (m_tail + 1) % m_size;

    return true;
}

void* PtrCircularQueue::Read()
{
    uint32_t tmptail = m_tail;
    if (m_head == tmptail)
    {
        return NULL;
    }
    void* ret = m_buffer[m_head];
    m_head = (m_head + 1) % m_size;

    return ret;
}
