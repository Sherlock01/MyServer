#include "circular_queue_test.h"
#include "myrandom.h"

#include <iostream>
#include <cunistd>
/*
CircularQueue cirque(100);

void Read()
{
    char tmp[100] = {'0'};
    cirque.Read(tmp, 4);
    printf("read = %s\n", tmp);
}

void Write()
{
	std::string tmp = "test";
	cirque.Write(tmp.c_str(), tmp.length());
	printf("write = %s\n", tmp.c_str());
}

int main()
{
    Write();
    Read();
	return 0;
}
*/


ThreadRead::ThreadRead()
{
    m_readNormalCount = 0;
    m_readToEmptyCount = 0;
    m_readTooMuchFailedCount = 0;
    m_readEmptyFailedCount = 0;
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
        char str[10] = {'\0'};
        uint32_t num = HRandom::RandomUint(1, 5);
        bool ret = thread_cirque.Read(str, num);
        //printf("read num = %d, ret = %d\n", num, int(ret));
        if (false == ret)
        {
            ++ sleepcount;
            ++ lastfailedcount;
            if (lastfailedcount > 1000)
            {
                break;
            }
            usleep(1000);
        }
        else
        {
            m_str += std::string(str, num);
            lastfailedcount = 0;
        }
    }
    printf("read sleepcount = %d\n", sleepcount - lastfailedcount);
    StopRead();
}
void ThreadRead::StopRead()
{
    //printf("readNormalCount = %d, readToEmptyCount = %d, readTooMuchFailedCount = %d, readEmptyFailedCount = %d\n", m_readNormalCount, m_readToEmptyCount, m_readTooMuchFailedCount, m_readEmptyFailedCount);
    Stop();
    m_stoped = true;
}

ThreadWrite::ThreadWrite()
{
    m_writeNormalCount = 0;
    m_writeToFullCount = 0;
    m_writeTooMuchFailedCount = 0;
    m_writeAlreadyFullFailedCount = 0;
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
        uint32_t num = HRandom::RandomUint(10, 18);
        char str[10] = {'\0'};
        for (uint32_t i = 0; i < num; ++i)
        {
            str[i] = HRandom::RandomCharA2Z();
        }
        bool ret = thread_cirque.Write(str, num); 
        if (false == ret)
        {
            ++ sleepcount;
            usleep(1000);
        }
        else
        {
            m_str += std::string(str, num);
        }
    }
    printf("write sleepcount = %d\n", sleepcount);
    StopWrite();
}

void ThreadWrite::StopWrite()
{
    //printf("writeNormalCount = %d, writeToFullCount = %d, writeTooMuchFailedCount = %d, writeAlreadyFullFailedCount = %d\n", m_writeNormalCount, m_writeToFullCount, m_writeTooMuchFailedCount, m_writeAlreadyFullFailedCount);
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
            std::string readstr = tread.Str();
            std::string writestr = twrite.Str();
            printf("read_size = %d, write_size = %d, dist = %d\n", (int)readstr.size(), (int)writestr.size(), (int)(writestr.size() - readstr.size()));
            if (readstr == writestr)
            {
                printf("success\n"); 
            }
            else
            {
                printf("failed\n"); 
            }
            for (size_t i = 0; i < readstr.size() && i < writestr.size(); ++i)
            {
                if (readstr[i] != writestr[i])
                {
                    printf("not equel index = %d\n", (int)i);
                    break;
                }
            }
            //std::cout << readstr << std::endl;
            //std::cout << writestr << std::endl;
            //std::cout << std::string(readstr.begin(), readstr.begin() + 100) << std::endl;
            //std::cout << std::string(writestr.begin(), writestr.begin() + 100) << std::endl;
            break;
        }
    }

    return 0;
}
