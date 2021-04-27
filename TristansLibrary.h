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
    Randumb(unsigned long long seed);

    unsigned long long Next();
    int NextRanged(int min, int max);
    float NextFloat0To1();
    float NextRangedFloat(float min, float max);
    bool CoinFlip();
};

unsigned int randumb32(void);
unsigned short randumb16(void);
unsigned int lfsr113_Bits(void);


//bool AABBIsInFrustumPlanes(Float3* corners, Plane* planes);


void setBit(int& bytes, int bitIndex, bool value);
bool getBit(int bytes, int bitIndex);
void setByte(int& bytes, char byte, char byteIndex);
char getByte(int bytes, char byteIndex);
char bitCount(int bytes);
char bitHighCount(int bytes);
char bitLowCount(int bytes, char stopIndex);
int getBits(int bytes, char startIndex, char stopIndex);
int shiftBitsRightFromIndex(int bytes, char index, unsigned char shift);


void addIntNoOverflowOrUnderflow(int& n, int add);
void addUnsignedIntNoOverflowOrUnderflow(unsigned int& n, int add);
float averageInt(int* ints, int size);
float averageFloat(float* floats, int size);
int powInt(int n, unsigned short p);
unsigned short isqrt16(unsigned short n);
unsigned int isqrt(unsigned int n);

unsigned int fastIntDistSqr(int* a, int* b);
int dotProductInt3(int* a, int* b);
void addIntArrays(int* dest, int* n, int size);
void addInt3s(int* dest, int* n);
void add3Int3s(int* dest, int* n, int* n1);
void subInt3s(int* dest, int* n);
void multInt3ByInt(int* dest, int n);
void multInt3s(int* dest, int* n);
void localIntPointToWorldSpace(int* right, int* up, int* forward, int* p, int* returnPtr);
