#pragma once

#include <bitset>

namespace cytrus {
#define BIT(X) 1 << X

#ifdef _WIN32
#define OS_SEP '\\'
#else
#define OS_SEP '/'
#endif

typedef char byte;
typedef unsigned char uByte;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef long long i128;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef size_t size;
typedef const void *offsetPtr;

typedef float f32;
} // namespace cytrus
