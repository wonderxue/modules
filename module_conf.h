#ifndef __MODULE_CONF__
#define __MODULE_CONF__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************mcu type define*******************************/
/*
*USE_MCU_8 use 8 bits mcu
*USE_MCU_32 use 32 bits mcu
*/
#define _MCU_TYPE  _MCU_8
/*****************************mcu type define*******************************/

/*****************************module log define*******************************/
#if 1
/*
*_log_level=0  =>disable logreport
*_log_level=1  =>only report errors
*_log_level=2  =>report both errors and warnings
*_log_level=3  =>report everything
*/
#define _log_level 3
#endif
/*****************************module log define*******************************/

/*****************************module spi define*******************************/
#if 1
//hardware pin define
#define _spi_pinSDI    2
#define _spi_pinSDO    3
#define _spi_pinSCLK   4
#endif
/*****************************module spi define*******************************/

/*****************************module i2c define*******************************/
#if 1
//hardware pin define
#define _i2c_pinSDA     13
#define _i2c_pinSCL     12
#endif
/*****************************module i2c define*******************************/

/*****************************module tft define*******************************/
#if 1
//hardware pin define
#define _tft_pinRST         4
#define _tft_pinRS          5
#define _tft_pinLED         15
#define _tft_pinCS          2
#endif
/*****************************module tft define*******************************/

/*****************************module sd_spi define*******************************/
#if 1
//hardware pin define
#define _sd_pinCS         5
#endif
/*****************************module sd_spi define*******************************/

/*****************************module oled define*******************************/
#if 1
//nothing to define
#endif
/*****************************module oled define*******************************/
/*****************************module mpu define*******************************/
#if 1
//nothing to define
#endif
/*****************************module mpu define*******************************/

/*****************************module lvgl define*******************************/
#if 1
//to keep lvgl structure,its configuration and porting file are "./lv_config" and "./lvgl/porting/" 
#endif
/*****************************module lvgl define*******************************/

/*****************************basical define*******************************/
//logic
#define _TRUE  1
#define _FALSE 0
//gpio
#define _gpio_IN 0
#define _gpio_OUT 1
#define _gpio_HIGH 1
#define _gpio_LOW 0

//basic type
#define _MCU_8  8
#define _MCU_32 32
#if (_MCU_TYPE!=_MCU_8)&&(_MCU_TYPE!=_MCU_32)
    #error please define _MCU_TYPE as _MCU_8 or _MCU_32
#endif
#define basicTypeCheck()  {\
if(sizeof(_base8)!=1||sizeof(_base16)!=2||sizeof(_base32)!=4||sizeof(_base64)!=8)\
    logReport(1,"module_conf.h","basicTypeCheck","basic type define error");\
}
#if _MCU_TYPE==_MCU_8
typedef unsigned char _ubase8;
typedef char _base8;
typedef unsigned short _ubase16;
typedef short _base16;
typedef unsigned long _ubase32;
typedef long _base32;
typedef unsigned long long _ubase64;
typedef long long _base64;
#endif
#if _MCU_TYPE==_MCU_32
typedef unsigned char _ubase8;
typedef char _base8;
typedef unsigned short _ubase16;
typedef short _base16;
typedef unsigned int _ubase32;
typedef int _base32;
typedef unsigned long long _ubase64;
typedef long long _base64;
#endif
/*****************************basical define*******************************/
#ifdef __cplusplus
}
#endif
#endif  //__MODULE_CONF__