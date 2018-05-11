#include "ptr_circular_queue_test.h"
#include "myrandom.h"

#include <iostream>
#include <cunistd>

ThreadRead::ThreadRead()
{
    m_stoped = true;
}

void ThreadRead::StartRead()
{
    m_stoped = false;
    Start(); 
}
void ThreadRead::Run()
{
    int sleepcount = 0;
    int lastfailedcount = 0;
    while(true)
    {
        void* ptr = NULL;
        //uint32_t num = HRandom::RandomUint(1, 5);
        ptr = thread_cirque.Read();
        if (NULL == ptr)
        {
            ++ sleepcount;
            ++ lastfailedcount;
            if (lastfailedcount > 1000)
            {
                break;
            }
            usleep(2000);
        }
        else
        {
            m_vec.push_back(ptr);
            lastfailedcount = 0;
        }
    }
    printf("read sleepcount = %d\n", sleepcount - lastfailedcount);
    StopRead();
}
void ThreadRead::StopRead()
{
    Stop();
    m_stoped = true;
}

ThreadWrite::ThreadWrite()
{
    m_stoped = true;
}

void ThreadWrite::StartWrite()
{
   m_stoped = false;
   Start(); 
}

void ThreadWrite::Run()
{
    int wcount = 10000;
    int sleepcount = 0;
    while (wcount--)
    {
        //uint32_t num = HRandom::RandomUint(1, 18);
        //for (uint32_t i = 0; i < num; ++i)
        //{
            //str[i] = HRandom::RandomCharA2Z();
        //}
        void* ptr = (void*)(new int);
        bool ret = thread_cirque.Write(ptr); 
        if (false == ret)
        {
            ++ sleepcount;
            delete ((int*)(ptr));
            usleep(1000);
        }
        else
        {
            m_vec.push_back(ptr);
        }
    }
    printf("write sleepcount = %d\n", sleepcount);
    StopWrite();
}

void ThreadWrite::StopWrite()
{
    Stop();
    m_stoped = true;
}

int main()
{
    ThreadRead tread;
    tread.StartRead();
    ThreadWrite twrite;
    twrite.StartWrite();

    while(true)
    {
        if(tread.Stoped() && twrite.Stoped())
        {
            std::vector<void*> readvec = tread.Vec();
            std::vector<void*> writevec = twrite.Vec();
            printf("read_size = %d, write_size = %d\n", (int)readvec.size(), (int)writevec.size());
            bool flag = true;
            for (size_t i = 0; i < readvec.size() && i < writevec.size(); ++i)
            {
                if (readvec[i] != writevec[i])
                {
                    printf("not equel index = %d\n", (int)i);
                    flag = false;
                    break;
                }
                if (i < 10)
                {
                    //printf("%x %x\n", readvec[i], writevec[i]);
                    std::cout << readvec[i] << " " << writevec[i] << std::endl;
                }
            }
            if (flag)
            {
                printf("success\n");
            }
            else
            {
                printf("failed\n");
            }
            break;
        }
    }

    return 0;
}
