#pragma once
#include <iostream>

unsigned int randumb32(void);
unsigned short randumb16(void);
unsigned int lfsr113_Bits(void);

class Randumb
{
private:
    unsigned long long s;
public:
    Randumb(unsigned long long seed);
    unsigned long long Next();
};



