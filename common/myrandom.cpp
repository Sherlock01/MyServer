#include "myrandom.h"

#include <algorithm>

HRandom::HRandom()
{
    srand(time(NULL));
}

uint32_t HRandom::RandomUint(uint32_t min, uint32_t max)
{
    if (min == max) return min;
    if (min > max) std::swap(min, max);

    return rand()%(max-min+1)+min;
}

char HRandom::RandomCharA2Z()
{
    return 'A' + RandomUint(0, 25);
}

HRandom HRandom::GlobalHRandom;
