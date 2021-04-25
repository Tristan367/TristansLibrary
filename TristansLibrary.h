#pragma once
#include <ctime>

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

unsigned int randumb32(void);
unsigned short randumb16(void);
unsigned int lfsr113_Bits(void);

class Randumb
{
private:
    unsigned long long s;
public:
    Randumb();
    Randumb(unsigned long long seed);

    unsigned long long Next();
    int NextRanged(int min, int max);
    float NextFloat0To1();
    float NextRangedFloat(float min, float max);
    bool CoinFlip();
};

class Float3
{
public:
    float x, y, z;
    Float3();
    Float3(float x, float y, float z);

    Float3 operator*(float f);
    Float3 operator+(Float3 v);
    float DotProduct(Float3 v);
};

class Transform 
{
public:
    Float3 right, up, forward, position;
    Transform();
    Transform(Float3 right, Float3 up, Float3 forward);
    Transform(Float3 right, Float3 up, Float3 forward, Float3 position);
    Transform(Float3 position);

    Float3 LocalPointToWorldSpace(Float3 p);
};

class Plane {
public:
    Float3 a, b, c, normal;
    Plane();
    Plane(Float3 a, Float3 b, Float3 c);
    Plane(Float3 a, Float3 b, Float3 c, Float3 norm);

    bool PointIsOnPositiveSideOfPlane(Float3 point);
};

void addIntNoOverflowOrUnderflow(int& n, int add);
void addUnsignedIntNoOverflowOrUnderflow(unsigned int& n, int add);

float averageInt(int* ints, int size);
float averageFloat(float* floats, int size);


