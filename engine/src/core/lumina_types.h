#pragma once

/*
	This header contains type declaration for primitive types, abstracted, platform independent, architecture independent
*/

// Represent a CHAR type (8 bit 1 Byte)
typedef char l_char8;
constexpr char l_char8_size = 0x1;

// Represent a BYTE type (8 bit unsigned 1 Byte)
typedef unsigned char l_byte8;
constexpr unsigned char l_byte8_size = 0x1;

// Represent a SHORT type (16 bit 2 Byte)
typedef short l_short16;
constexpr short l_short16_size = 0x2;

// Represent a USHORT type (16 bit unsigned 2 Byte)
typedef unsigned short l_ushort16;
constexpr unsigned short l_ushort16_size = 0x2;

// Represent a INT type (32 bit 4 Byte)
typedef int l_int32;
constexpr int l_int32_size = 0x4;

// Represent a UINT type (32 bit unsigned 4 Byte)
typedef unsigned int l_uint32;
constexpr unsigned int l_uint32_size = 0x4;

// Represent a FLOAT type (32 bit floating point 4 Byte)
typedef float l_float32;
constexpr float l_float32_size = 0x4;

// Represent a INT64 type (64 bit 8 Byte)
typedef long long l_int64;
constexpr long long l_int64_size = 0x8;

// Represent a UINT64 type (64 bit unsigned 8 Byte)
typedef unsigned long long l_uint64;
constexpr unsigned long long l_uint64_size = 0x8;

// Represent a DOUBLE type (64 bit floating point 8 Byte)
typedef double l_double64;
constexpr double l_double64_size = 0x8;

// Represent a UTF-8 string/charsequence pointer
typedef const char* l_cstr8;

// Represent a UTF-16 string/charsequence pointer (wide string)
typedef const wchar_t* l_cwstr8;

// Byte multipliers sizes
constexpr l_uint32 l_kbyte8_size = l_byte8_size * 1000;
constexpr l_uint32 l_mbyte8_size = l_kbyte8_size * 1000;
constexpr l_uint32 l_gbyte8_size = l_mbyte8_size * 1000;
constexpr l_uint32 l_tbyte8_size = l_gbyte8_size * 1000;