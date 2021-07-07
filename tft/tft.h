#ifndef __TFT_H__
#define __TFT_H__

#include "../module_conf.h"
#include "../spi/spi.h"

#ifdef __cplusplus
extern "C" {
#endif


extern void _gpio_Mode(_ubase8 gpioNum,_ubase8 gpioMode);
extern void _gpio_Write(_ubase8 gpioNum,_ubase8 gpioStatus);
extern void _time_delayMs(_ubase16 time);

#define _tft_LED_Out   _gpio_Mode(_tft_pinLED, _gpio_OUT)   
#define _tft_RS_Out    _gpio_Mode(_tft_pinRS, _gpio_OUT)
#define _tft_RST_Out   _gpio_Mode(_tft_pinRST, _gpio_OUT)
    
#define _tft_LED_H   _gpio_Write(_tft_pinLED, _gpio_HIGH)   
#define _tft_RS_H    _gpio_Write(_tft_pinRS, _gpio_HIGH)
#define _tft_RST_H   _gpio_Write(_tft_pinRST, _gpio_HIGH)
    
#define _tft_LED_L   _gpio_Write(_tft_pinLED, _gpio_LOW)
#define _tft_RST_L   _gpio_Write(_tft_pinRST, _gpio_LOW)
#define _tft_RS_L    _gpio_Write(_tft_pinRS, _gpio_LOW)

#define _tft_delayMs(x) _time_delayMs(x)

void tftInit(void);
void tftSetRegion(_ubase8 x_start,_ubase8 y_start,_ubase8 x_end,_ubase8 y_end);
void tftSetXY(_ubase8 x,_ubase8 y);
void tftDrawArea(_ubase8 x1,_ubase8 y1,_ubase8 x2,_ubase8 y2,_ubase16 *Data);
void tftClear(_ubase16 Color);

#ifdef __cplusplus
}
#endif

#endif  //__TFT_H__
