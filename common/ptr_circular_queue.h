#ifndef __PTR_CIRCULAR_QUEUE_H__
#define __PTR_CIRCULAR_QUEUE_H__

#include <cstdint>

class PtrCircularQueue
{
    public:
        PtrCircularQueue(uint32_t size);
        virtual ~PtrCircularQueue();

        bool Init(uint32_t size);
        void UnInit();

        bool Write(void* ptr);
        void* Read();

    protected:
        void** m_buffer;
        uint32_t m_size;
        uint32_t volatile m_head;
        uint32_t volatile m_tail;
};

#endif
