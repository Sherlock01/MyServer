#include "mythread.h"

void* ThreadStartRun(void* p)
{
    Thread* thread = (Thread*)p;
    thread->Run();

    return NULL;
}

Thread::Thread()
:m_threadID(0)
{
    
}

Thread::~Thread()
{
}

bool Thread::Start()
{
    int ret = pthread_create(&m_threadID, NULL, ThreadStartRun, (void*)this);
    if (0 != ret)
    {
        return false;
    }
    return true;
}

void Thread::Stop()
{
    pthread_cancel(m_threadID);
}

void Thread::Join()
{
    pthread_join(m_threadID, NULL);
}


