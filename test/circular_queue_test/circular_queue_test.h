#ifndef __CIRCULAR_QUEUE_TEST_H__
#define __CIRCULAR_QUEUE_TEST_H__
#include "circular_queue.h"
#include "mythread.h"

#include <cstdio>
#include <string>

CircularQueue thread_cirque(20);

class ThreadRead : public Thread
{
    public:
        ThreadRead();

        void StartRead();
        virtual void Run();
        void StopRead();

        std::string Str() { return m_str; }
        bool Stoped() { return m_stoped; }

    private:
        int m_readNormalCount;
        int m_readToEmptyCount;
        int m_readTooMuchFailedCount;
        int m_readEmptyFailedCount;

        std::string m_str;
        bool m_stoped;
};

class ThreadWrite : public Thread
{
    public:
        ThreadWrite();

        void StartWrite();
        virtual void Run();
        void StopWrite();

        std::string Str() { return m_str; }
        bool Stoped() { return m_stoped; }

    private:
        int m_writeNormalCount;
        int m_writeToFullCount;
        int m_writeTooMuchFailedCount;
        int m_writeAlreadyFullFailedCount;

        std::string m_str;
        bool m_stoped;
};

#endif
