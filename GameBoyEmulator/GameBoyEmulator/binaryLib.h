#ifndef DEF_BINARYLIB
#define DEF_BINARYLIB

typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

uint8 getBit(const uint8& byte, const int& bitIndex);
uint8 setBit(const uint8& byte, const int& bitIndex);
uint8 resetBit(const uint8& byte, const int& bitIndex);
bool testBit(const int& value, const int& bitNumber);


#endif
