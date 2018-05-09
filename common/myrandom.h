#ifndef __MYRANDOM_H__
#define __MYRANDOM_H__

#include <cstdlib>
#include <ctime>
#include <stdint.h>

class HRandom
{
    public:
        HRandom();

        static uint32_t RandomUint(uint32_t min, uint32_t max);
        static char RandomCharA2Z();

    private:
        static HRandom GlobalHRandom;
};

#endif

