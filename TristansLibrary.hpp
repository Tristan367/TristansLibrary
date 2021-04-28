#pragma once

const unsigned int uCap = ~0;
const int sCap = uCap >> 1;
const int sCapMin = -sCap - 1;

const unsigned short uCap16 = ~0;
const short sCap16 = uCap16 >> 1;
const short sCapMin16 = -sCap16 - 1;

const unsigned char uCap8 = ~0;
const char sCap8 = uCap8 >> 1;
const char sCapMin8 = -sCap8 - 1;

const double pi = 3.141592653589793238;
const double sqrRt2 = 1.414213562373095048;
const double sqrRt3 = 1.732050807568877293;
const double goldenRatio = 1.618033988749894848;

const float piF = 3.141592653f;
const float sqrRt2F = 1.414213562f;
const float sqrRt3F = 1.732050807f;
const float goldenRatioF = 1.618033988f;


class Randumb
{
private:
    unsigned long long s;
public:
    Randumb(unsigned long long seed) {
        s = seed;
    };

    unsigned long long Next() {
        s = s * 9 + 1; // modulus this by an odd number, an even number mod leads to alternating between odd and even numbers, therefore you also never get the same number twice or more in a row
        return s;
    }
    int NextRanged(int min, int max) {
        unsigned int width = max - min;
        int offset = max - width;
        return (Next() % width) + offset;
    }
    float NextFloat0To1() {
        int resolution = 1000000001;
        if (s < 111111111) { // to prevent several low numbers in a row everytime the seed is below the resolution / 9
            s *= 12345;
        }
        return (float)(Next() % resolution) / resolution;
    }
    float NextRangedFloat(float min, float max) {
        float r = NextFloat0To1();
        float width = max - min;
        float offset = max - width;
        return (width * r) + offset;
    }
    bool CoinFlip() {
        return (Next() % 100) >= 50;
    }
};

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
    z1 = z1 * 9 + 1;
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

void setBit(int& bytes, int bitIndex, bool value) {
    bytes &= ~(value << bitIndex);
}
bool getBit(int bytes, int bitIndex) {
    return (bytes & (1 << bitIndex)) > 0;
}
void setByte(int& bytes, char byte, char byteIndex) {
    char shift = 8 * byteIndex;
    bytes &= ~(15 << shift); // clearing the byte
    bytes |= byte << shift; // setting the byte
}
char getByte(int bytes, char byteIndex) {
    return (bytes >> (byteIndex * 8)) & 255;
}
char bitCount(int bytes) {
    int b = bytes;
    unsigned char count = 0;
    while (b > 0) {
        count++;
        b >>= 1;
    }
    return count;
}
char bitHighCount(int bytes) {
    int b = bytes;
    unsigned char count = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            count++;
        }
        b >>= 1;
    }
    return count;
}
char bitLowCount(int bytes, char stopIndex) {
    int b = bytes;
    unsigned char count = 0;
    char counter2 = 0;
    while (b > 0) {
        if (b % 2 == 0) {
            count++;
        }
        b >>= 1;
        counter2++;
        if (counter2 >= stopIndex) {
            break;
        }
    }
    return count;
}
int getBits(int bytes, char startIndex, char stopIndex) {
    return (bytes >> startIndex) & ~(~0 << stopIndex);
}
int shiftBitsRightFromIndex(int bytes, char index, unsigned char shift) {
    int bitsToKeepMask = ~0 << index;
    int bitsToKeep = bytes & bitsToKeepMask;
    int bH = bytes & ~bitsToKeepMask;
    bH >>= shift;
    bH |= bitsToKeep;
    return bH;
}

void addIntNoOverflowOrUnderflow(int& n, int add) {
    if (add >= 0) {
        if (n + add < n) {
            n = sCap;
            return;
        }
    }
    else {
        if (n + add > n) {
            n = sCapMin;
            return;
        }
    }
    n += add;
}

void addUnsignedIntNoOverflowOrUnderflow(unsigned int& n, int add) {

    if (add >= 0) {
        if (n + add < n) {
            n = uCap;
            return;
        }
    }
    else {
        if (n + add > n) {
            n = 0;
            return;
        }
    }
    n = n + add;
}
float averageInt(int* ints, int size) {
    int avg = 0;
    for (int i = 0; i < size; i++) {
        avg += ints[i];
    }
    return (float)avg / size;
}
float averageFloat(float* floats, int size) {
    float avg = 0;
    for (int i = 0; i < size; i++) {
        avg += floats[i];
    }
    return avg / size;
}
int powInt(int n, unsigned short p) {
    int nH = n;
    for (unsigned int i = 0; i < p; i++) {
        n *= nH;
    }
    return n;
}
unsigned short isqrt16(unsigned short num) {
    unsigned short res = 0;
    unsigned short bit = 1 << 14; // The second-to-top bit is set: 1L<<30 for long
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        }
        else
            res >>= 1;
        bit >>= 2;
    }
    return res;
}
unsigned int isqrt(unsigned int num) {
    unsigned int res = 0;
    unsigned int bit = 1 << 30; // The second-to-top bit is set: 1L<<30 for long // "bit" starts at the highest power of four <= the argument.
    while (bit > num) {
        bit >>= 2;
    }
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        }
        else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return res;
}

unsigned int fastIntDistSqr(int* a, int* b) {
    int x = a[0] - b[0];
    int y = a[1] - b[1];
    int z = a[2] - b[2];
    return (x * x) + (y * y) + (z * z);
}
unsigned int distSqr(float* a, float* b) {
    float x = a[0] - b[0];
    float y = a[1] - b[1];
    float z = a[2] - b[2];
    return (x * x) + (y * y) + (z * z);
}
int dotProductInt3(int* a, int* b) {
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}
void addIntArrays(int* dest, int* n, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] += n[i];
    }
}
void addInt3s(int* dest, int* n) {
    dest[0] += n[0];
    dest[1] += n[1];
    dest[2] += n[2];
}
void add3Int3s(int* dest, int* n, int* n1) {
    dest[0] += n[0] + n1[0];
    dest[1] += n[1] + n1[1];
    dest[2] += n[2] + n1[2];
}
void subInt3s(int* dest, int* n) {
    dest[0] -= n[0];
    dest[1] -= n[1];
    dest[2] -= n[2];
}
void multInt3ByInt(int* dest, int n) {
    dest[0] *= n;
    dest[1] *= n;
    dest[2] *= n;
}
void multInt3s(int* dest, int* n) {
    dest[0] *= n[0];
    dest[1] *= n[1];
    dest[2] *= n[2];
}
void multFloat3ByInt(float* dest, int n) {
    dest[0] *= n;
    dest[1] *= n;
    dest[2] *= n;
}
void multFloat3ByF(float* dest, float n) {
    dest[0] *= n;
    dest[1] *= n;
    dest[2] *= n;
}
void add3Float3s(float* dest, float* n, float* n1) {
    dest[0] += n[0] + n1[0];
    dest[1] += n[1] + n1[1];
    dest[2] += n[2] + n1[2];
}

void localPointToWorldSpace(float* right, float* up, float* forward, float* p, float* returnPtr) {

    float r[3] = { right[0], right[1], right[2] };
    float u[3] = { up[0], up[1], up[2] };
    float f[3] = { forward[0], forward[1], forward[2] };

    multFloat3ByF(r, p[0]);
    multFloat3ByF(u, p[1]);
    multFloat3ByF(f, p[2]);

    add3Float3s(r, u, f);

    returnPtr[0] = r[0];
    returnPtr[1] = r[1];
    returnPtr[2] = r[2];
}

/*
bool intAABBIsInFrustumPlanes(int* corners, float* planes)
{
    bool inFrustum;
    for (int i = 0; i < 6; i++)
    {
        inFrustum = false;
        for (int j = 0; j < 8; j++)
        {
            if (planes[i].PointIsOnPositiveSideOfPlane(corners[j]))
            {
                inFrustum = true;
            }
        }
        if (!inFrustum)
        {
            return false;
        }
    }
    return true;
}*/