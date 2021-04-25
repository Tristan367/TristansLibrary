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

Randumb::Randumb() {
    time_t t;
    time(&t);
    s = t;
}
Randumb::Randumb(unsigned long long seed) {
    s = seed;
};
unsigned long long Randumb::Next() {
    s = (s * 9 + 1); // modulus this by an odd number, an even number mod leads to alternating between odd and even numbers, therefore you also never get the same number twice or more in a row
    return s;
}
int Randumb::NextRanged(int min, int max) {
    unsigned int width = max - min;
    int offset = max - width;
    return (Next() % width) + offset;
}
float Randumb::NextFloat0To1() {
    int resolution = 1000000001;
    if (s < 111111111) { // to prevent several low numbers in a row everytime the seed is below the resolution / 9
        s *= 12345;
    }
    return (float)(Next() % resolution) / resolution;
}
float Randumb::NextRangedFloat(float min, float max) {
    float r = NextFloat0To1();
    float width = max - min;
    float offset = max - width;
    return (width * r) + offset;
}
bool Randumb::CoinFlip() {
    return (Next() % 100) >= 50;
}


Float3::Float3() {
    x = 0;
    y = 0;
    z = 0;
};
Float3::Float3(float xC, float yC, float zC) {
    x = xC;
    y = yC;
    z = zC;
}
Float3 Float3::operator*(float f) {
    Float3 ret(x, y, z);
    ret.x *= f;
    ret.y *= f;
    ret.z *= f;
    return ret;
}
Float3 Float3::operator+(Float3 v) {
    Float3 ret(x, y, z);
    ret.x += v.x;
    ret.y += v.y;
    ret.z += v.z;
    return ret;
}
float Float3::DotProduct(Float3 v) {
    return (x * v.x) + (y * v.y) + (z * v.z);
}


Plane::Plane() {
    a = Float3();
    b = Float3();
    c = Float3();
}
Plane::Plane(Float3 aC, Float3 bC, Float3 cC) {
    a = aC;
    b = bC;
    c = cC;
}
Plane::Plane(Float3 aC, Float3 bC, Float3 cC, Float3 norm) {
    a = aC;
    b = bC;
    c = cC;
    normal = norm;
}
// TODO: this function
bool Plane::PointIsOnPositiveSideOfPlane(Float3 p) {


}


Transform::Transform() {
    right = Float3();
    up = Float3();
    forward = Float3();
    position = Float3();
}
Transform::Transform(Float3 r, Float3 u, Float3 f) {
    right = r;
    up = u;
    forward = f;
    position = Float3();
}
Transform::Transform(Float3 r, Float3 u, Float3 f, Float3 p) {
    right = r;
    up = u;
    forward = f;
    position = p;
}
Transform::Transform(Float3 p) {
    right = Float3();
    up = Float3();
    forward = Float3();
    position = p;
}
Float3 Transform::LocalPointToWorldSpace(Float3 p) {
    Float3 u1 = right * p.x;
    Float3 u2 = up * p.y;
    Float3 u3 = forward * p.z;
    return u1 + u2 + u3;
}


bool AABBIsInFrustumPlanes(Float3*corners, Plane *planes)
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
}


// miscellaneous functions

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
    n = n + add;
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
