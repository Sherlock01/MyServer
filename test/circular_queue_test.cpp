#include "../common/ptr_circular_queue.h"

#include <cstdio>
#include <string>

CircularQueue cirque(100);

void Read()
{
	char tmp[100] = {'0'};
	cirque.Read(tmp, 4);
	printf("read = %s", tmp);
}

void Write()
{
	std::string tmp = "test";
	cirque.Write(tmp.c_str(), tmp.length());
	printf("write = %s", tmp.c_str());
}

int main()
{
	Write();
	Read();
	return 0;
}