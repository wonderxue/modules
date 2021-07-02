#ifndef __BASIC_TYPE_DEF__
#define __BASIC_TYPE_DEF__
#if (!defined USE_MCU_8)&&(!defined USE_MCU_32)
    #error please define USE_MCU_8 or USE_MCU_32
#endif
#define basicTypeCheck()  {\
if(sizeof(_base8)!=1||sizeof(_base16)!=2||sizeof(_base32)!=4||sizeof(_base64)!=8)\
    logReport(1,"--basic_type_def.h--","basicTypeCheck:basic type define error");\
}
#ifdef USE_MCU_8
typedef unsigned char _ubase8;
typedef char _base8;
typedef unsigned short _ubase16;
typedef short _base16;
typedef unsigned long _ubase32;
typedef long _base32;
typedef unsigned long long _ubase64;
typedef long long _base64;
#endif
#ifdef USE_MCU_32
typedef unsigned char _ubase8;
typedef char _base8;
typedef unsigned short _ubase16;
typedef short _base16;
typedef unsigned int _ubase32;
typedef int _base32;
typedef unsigned long long _ubase64;
typedef long long _base64;
#endif
#endif  //__BASIC_TYPE_DEF__