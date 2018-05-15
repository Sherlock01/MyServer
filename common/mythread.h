#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__

#include <cstdint>
#include <pthread.h>

class Thread
{
    public:
        Thread();
        ~Thread();

        bool Start();
        void Stop();
        void Join();

        virtual void Run() = 0;

    protected:
        pthread_t m_threadID;
};

#endif
