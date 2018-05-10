#ifndef __PTR_CIRCULAR_QUEUE_TEST_H__
#define __PTR_CIRCULAR_QUEUE_TEST_H__
#include "ptr_circular_queue.h"
#include "mythread.h"

#include <cstdio>
#include <string>
#include <vector>

PtrCircularQueue thread_cirque(4);

class ThreadRead : public Thread
{
    public:
        ThreadRead();

        void StartRead();
        virtual void Run();
        void StopRead();

        bool Stoped() { return m_stoped; }
        std::vector<void*>& Vec() { return m_vec;}

    private:

        std::vector<void*> m_vec;
        bool m_stoped;
};

class ThreadWrite : public Thread
{
    public:
        ThreadWrite();

        void StartWrite();
        virtual void Run();
        void StopWrite();

        bool Stoped() { return m_stoped; }
        std::vector<void*>& Vec() { return m_vec;}

    private:

        std::vector<void*> m_vec;
        bool m_stoped;
};

#endif
