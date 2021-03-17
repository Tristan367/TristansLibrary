#include "TristansLibrary.h"

unsigned int randumb32(void) { 
    static unsigned int z1 = 3, z2 = 7, z3 = 13, z4 = 19;
    z1 = z1 * 9 + 1; // equation gets all 4,294,967,296 numbers
    if (z1 == 3) {
        z2 = z2 * 9 + 1;
        if (z2 == 7) {
            z3 = z3 * 9 + 1;
            if (z3 == 13) {
                z4 = z4 * 9 + 1;
            }
        }
    }
    return (z1 ^ z2 ^ z3 ^ z4);
    // 2^128 long pattern or 3.4 * 10^38
    // at 500 million a second, it would take you 21,580,566,141,612,028,377,941 years to compute all numbers
    // even China's 10 million processor supercomputer would still take 2 quadrillion years to compute
    // it is about 20X faster than rand() and about 5X faster than lfsr113_Bits()
}
unsigned short randumb16(void) {
    static unsigned short z1 = 3, z2 = 7, z3 = 13, z4 = 19;
    z1 = z1 * 9 + 1; // equation gets all 65536 numbers
    if (z1 == 3) {
        z2 = z2 * 9 + 1;
        if (z2 == 7) {
            z3 = z3 * 9 + 1;
            if (z3 == 13) {
                z4 = z4 * 9 + 1;
            }
        }
    }
    return (z1 ^ z2 ^ z3 ^ z4);
}
unsigned int lfsr113_Bits(void)
{
    static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
    unsigned int b;
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    return (z1 ^ z2 ^ z3 ^ z4);
}

Randumb::Randumb(unsigned long long seed) {
    s = seed;
};
unsigned long long Randumb::Next() {
    s = s * 9 + 1;
    return s;
}





