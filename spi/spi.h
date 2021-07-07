#ifndef __SPI_H__
#define __SPI_H__

#include "../module_conf.h"
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

extern void _gpio_Mode(_ubase8 gpioNum,_ubase8 gpioMode);
extern void _gpio_Write(_ubase8 gpioNum,_ubase8 gpioStatus);
extern _ubase8 _gpio_Read(_ubase8 gpioNum);
extern void _time_delayUs(_ubase16 time);

#define _spi_SDI_In     _gpio_Mode(_spi_pinSDI,_gpio_IN)
#define _spi_SDO_Out    _gpio_Mode(_spi_pinSDO,_gpio_OUT)
#define _spi_SCLK_Out   _gpio_Mode(_spi_pinSCLK,_gpio_OUT)

#define _spi_SDI_Read   _gpio_Read(_spi_pinSDI)
#define _spi_SDO_H      _gpio_Write(_spi_pinSDO,_gpio_HIGH)
#define _spi_SDO_L      _gpio_Write(_spi_pinSDO,_gpio_LOW)
#define _spi_SCLK_H     _gpio_Write(_spi_pinSCLK,_gpio_HIGH)
#define _spi_SCLK_L     _gpio_Write(_spi_pinSCLK,_gpio_LOW)

#define _spi_DelayUs(x)   _time_delayUs(x)

struct spiMode
{
    /*  
    Mode0:CPOL=0,CPHA=0
    Mode1:CPOL=0,CPHA=1
    Mode2:CPOL=1,CPHA=0
    Mode3:CPOL=1,CPHA=1
    CPOL:spi时钟信号电平（1:空闲时高电平; 0:空闲时低电平）
    CPHA:spi时钟信号采样（0:第一个边沿开始; 1:第二个边沿开始）
    */
    _ubase8 spi_Mode_0;
    _ubase8 spi_Mode_1;
    _ubase8 spi_Mode_2;
    _ubase8 spi_Mode_3;
};
extern struct spiMode spiMode;
//功能定义
void spiSetFrequency(_ubase8 delayPeriod);
_ubase8 spiRegist(_ubase8 spiSelectPin);
_ubase8 *spiMultiByteTransfer(_ubase8 fd, const _ubase8 *data, _ubase8 byteNum, _ubase8 spiMode);

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__