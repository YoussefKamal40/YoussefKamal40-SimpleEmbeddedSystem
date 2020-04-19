#ifndef STD_TYPES_H_H_
#define STD_TYPES_H_H_
typedef unsigned char u8 ;
typedef signed char  s8; 
typedef  unsigned short int u16;
typedef  signed short int s16;
typedef  unsigned long int u32;
typedef  signed long int s32;
typedef  float f32;
typedef  double f64;

typedef  u8* pu8 ;
typedef   s8* ps8;
typedef   u16* pu16;
typedef   s16* ps16;
typedef   u32* pu32;
typedef  s32* ps32;
typedef   f32* pf32;
typedef   f64* pf64;
typedef unsigned char error_type;

#define NULL		((void *)0)

#define OK	0
#define NOK	1
#endif
