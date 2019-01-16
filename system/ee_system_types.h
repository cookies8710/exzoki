/*
  Project name:	    Exzoki engine
  Author:			Tomas Surovec
  Date & time:		18.1.05 15:22
  Description:		ee_system_types.h
  History:
  --------------------------------
  18.11.2005 - Created
*/

#ifndef EE_SYSTEM_TYPES_H
#define EE_SYSTEM_TYPES_H

// Konstanty
#define EE_FALSE 0
#define EE_TRUE 1
#define EE_NULL 0
#define EE_NEVERENDINGLOOP 1

// Celoèíselné typy
typedef unsigned char EE_BYTE_t;
typedef char EE_CHAR_t;
typedef unsigned short int EE_U16_t;
typedef signed short int EE_S16_t;
typedef unsigned long int EE_U32_t;
typedef signed long int EE_S32_t;
typedef unsigned long long int EE_U64_t;
typedef signed long long int EE_S64_t;

// Typy s plovoucí desetinnou èárkou
typedef float EE_FLOAT_t;
typedef double EE_DOUBLE_t;
typedef long double EE_LDOUBLE_t;

// Ukazatele
typedef void* EE_PVOID_t; 
typedef EE_BYTE_t* EE_PBYTE_t;
typedef EE_CHAR_t* EE_PCHAR_t;
typedef EE_U16_t* EE_PU16_t;
typedef EE_S16_t* EE_PS16_t;
typedef EE_U32_t* EE_PU32_t;
typedef EE_S32_t* EE_PS32_t;
typedef EE_U64_t* EE_PU64_t;
typedef EE_S64_t* EE_PS64_t;
typedef EE_FLOAT_t* EE_PFLOAT_t;
typedef EE_DOUBLE_t* EE_PDOUBLE_t;

// Konstantní ukazatele
typedef const EE_BYTE_t* EE_CPBYTE_t;
typedef const EE_CHAR_t* EE_CPCHAR_t;
typedef const EE_U16_t* EE_CPU16_t;
typedef const EE_S16_t* EE_CPS16_t;
typedef const EE_U32_t* EE_CPU32_t;
typedef const EE_S32_t* EE_CPS32_t;
typedef const EE_U64_t* EE_CPU64_t;
typedef const EE_S64_t* EE_CPS64_t;
typedef const EE_FLOAT_t* EE_CPFLOAT_t;
typedef const EE_DOUBLE_t* EE_CPDOUBLE_t;

// Ostatní
typedef EE_PCHAR_t EE_CSTRING_t;
typedef EE_CPCHAR_t EE_CCSTRING_t;
typedef EE_BYTE_t EE_BOOL_t;

// Èas
struct EE_SYSTEM_TIME_s
{
 EE_U16_t u16_Year;
 EE_BYTE_t b_Month; // 1 = leden, 2 = únor, atd. 
 EE_BYTE_t b_Day;
 EE_BYTE_t b_Hour;   
 EE_BYTE_t b_Minute;
 EE_BYTE_t b_Second;
 EE_BYTE_t b_DayOfWeek; // 0 = nedìle, 1 = pondìlí, atd. 
};

// Barva
struct EE_SYSTEM_COLOR_s
{
    EE_BYTE_t b_R, b_G, b_B, b_A;    
};

#endif
