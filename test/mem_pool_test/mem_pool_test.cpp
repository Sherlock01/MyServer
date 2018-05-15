#include "mem_pool_test.h"

#include "myrandom.h"

#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

std::string GetNumString(uint32_t num)
{
	std::string str;
	for (uint32_t i = 0; i < num; ++i)
	{
		str.push_back(HRandom::RandomCharA2Z());
	}
	return str;
}

void TestBuffer()
{
	int perfect = 0, normal = 0, failed = 0;
	for (uint32_t i = 2; i < 1000; i = i + HRandom::RandomUint(uint32_t(1), uint32_t(20)))
	{
		MemBuffer* buffer = new MemBuffer(i);

		std::string strin, strout;
		int w_0 = 0, w_n = 0, w_f = 0, w_e = 0;
		int r_0 = 0, r_n = 0, r_e = 0, r_f = 0;
		while (buffer->LeftSpace() || buffer->DataSize())
		{
			uint32_t wnum = HRandom::RandomUint(1, buffer->LeftSpace() * 2);
			if (0 == wnum) wnum = 1;
			std::string str = GetNumString(wnum);
			if (buffer->Write(str.c_str(), str.length()))
			{
				strin += str;
				if (buffer->DataSize() == str.length())
				{
					w_0 ++;
				}
				else
				{
					w_n ++;
				}
				if (buffer->LeftSpace() == 0)
				{
					w_e ++;
				}
			}
			else
			{
				w_f ++;
			}
			char cstr[1001] = {'\0'};
			uint32_t rnum = HRandom::RandomUint(1, buffer->DataSize() * 2);
			if (0 == rnum) rnum = 1;
			if (buffer->ReadAndRemove(cstr, rnum))
			{
				strout += std::string(cstr, rnum);
				if (buffer->DataSize() == 0)	
				{
					r_e ++;
				}
				else
				{
					r_n ++;
				}
			}
			else
			{
				if (buffer->DataSize() == 0)
				{
					r_0 ++;
				}
				else
				{
					r_f ++;
				}
			}
		}
		delete buffer;
		if (strin == strout && strin.size() == i)
		{
			if (w_0 && w_n && w_e && w_n && r_0 && r_e && r_n && r_f)
			{
				printf("perfect success in = %d out = %d i = %d\n", (int)strin.size(), (int)strout.size(), i);
				perfect ++;
			}
			else
			{
				printf("normal success in = %d out = %d i = %d\n", (int)strin.size(), (int)strout.size(), i);
				normal ++;
			}
		}
		else
		{
			printf("failed in = %d out = %d i = %d\n", (int)strin.size(), (int)strout.size(), i);
			failed ++;
		}
	}
	printf("perfect = %d, normal = %d, failed = %d\n", perfect, normal, failed);
}

void BufferListPrint(MemList& list, std::vector<MemBuffer*>& vec) 
{
	printf("size = %d, allcount = %d\n", list.Size(), list.AllCount());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";	
	}
	for (int i = list.Members().size() - 1; i >= 0; --i)
	{
		cout << list.Members()[i] << " ";
	}
	cout << endl;
}

void TestBufferList()
{
	uint32_t capacity = 32;
	MemList list(capacity);
	std::vector<MemBuffer*> vec;
	vec.push_back(list.Borrow());
	BufferListPrint(list, vec);
	vec.push_back(list.Borrow());
	BufferListPrint(list, vec);
	list.GiveBack(vec.back());
	vec.pop_back();
	BufferListPrint(list, vec);
	vec.push_back(list.Borrow());
	BufferListPrint(list, vec);
	vec.push_back(list.Borrow());
	BufferListPrint(list, vec);
	sleep(6);
	list.CheckFree(time(NULL));
	BufferListPrint(list, vec);
	for (int i = vec.size() - 1; i >= 0; --i)
	{
		list.GiveBack(vec[i]);
	}
	vec.clear();
	BufferListPrint(list, vec);
	while(list.Size())
	{
		sleep(3);
		list.CheckFree(time(NULL));
		BufferListPrint(list, vec);
	}
	BufferListPrint(list, vec);
}

void PoolPrint(MemPool& pool, vector<MemBuffer*>& vec)
{
	cout << "POOL PRINT" << endl;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		cout << "vec: " << vec[i] << " " << vec[i]->Capacity() << endl;;
	}
	auto& poolMap = pool.PoolMap();
	for (auto i = poolMap.begin(); i != poolMap.end(); ++i)
	{
		cout << (i->first) << endl;
		MemList& list = (*(i->second));
		for (size_t j = 0; j < list.Members().size(); ++j)
		{
			cout << "pool: " << list.Members()[j] << " " << list.Members()[j]->Capacity() << endl;
		}
	}
}

void TestBufferPool()
{
	vector<MemBuffer*> vec;
	MemPool pool;
	for (uint32_t i = 2; i < 20; i = i + 2)
	{
		bool flag = false;
		MemBuffer* buffer = pool.Borrow(i);
		if (buffer)
		{
			vec.push_back(buffer);
		}
		else
		{
			 flag = true;
		}
		buffer = pool.Borrow(i + 1);
		if (buffer)
		{
			vec.push_back(buffer);
		}
		else
		{
			 flag = true;
		}
		while (!vec.empty())
		{
			pool.GiveBack(vec.back());
			vec.pop_back();
		}
		PoolPrint(pool, vec);
		if (flag)
		{
			break;
		}
	}
	while(!pool.PoolMap().empty())
	{
		pool.Update(time(NULL));
	}
	PoolPrint(pool, vec);
}

int main()
{
	//TestBuffer();
	//TestBufferList();
	TestBufferPool();
	return 0;
}