#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

class CircularQueue
{
    public:
        CircularQueue();
        ~CircularQueue();

        bool init();
        void unInit();

        bool write(char* pStr, uint32_t len);
        bool read(char* pStr, uint32_t len);

        uint32_t left();

    private:
        char* m_pBuffer;
        uint32_t m_nSize;
        char* volatile m_pHead;
        char* volatile m_pTail;
};

#endif
