#include "mem_pool_test.h"

#include "myrandom.h"

#include <string>

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

void TestBufferList()
{

}

void TestBufferPool()
{

}

int main()
{
	//TestBuffer();
	return 0;
}