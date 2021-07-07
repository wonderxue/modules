#ifndef __I2C_H__
#define __I2C_H__
#include "../module_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void _gpio_Mode(_ubase8 gpioNum,_ubase8 gpioMode);
extern void _gpio_Write(_ubase8 gpioNum,_ubase8 gpioStatus);
extern _ubase8 _gpio_Read(_ubase8 gpioNum);
extern void _time_delayUs(_ubase16 time);

#define _i2c_SCL_L   _gpio_Write(_i2c_pinSCL,_gpio_LOW)
#define _i2c_SCL_H   _gpio_Write(_i2c_pinSCL,_gpio_HIGH)
#define _i2c_SDA_L   _gpio_Write(_i2c_pinSDA,_gpio_LOW)
#define _i2c_SDA_H   _gpio_Write(_i2c_pinSDA,_gpio_HIGH)
#define _i2c_SDA_In  _gpio_Mode(_i2c_pinSDA,_gpio_IN)
#define _i2c_SDA_Out _gpio_Mode(_i2c_pinSDA,_gpio_OUT)
#define _i2c_SCL_Out _gpio_Mode(_i2c_pinSCL,_gpio_OUT)
#define _i2c_SDA_Read _gpio_Read(_i2c_pinSDA)
#define _i2c_DelayUs(x) _time_delayUs(x)

//功能定义
_ubase8 i2cBegin(_ubase8 dev_addr);
void i2cSetTimeOut(_ubase8 count);
_Bool i2cWriteByte(_ubase8 fid,_ubase8 data);
_Bool i2cWriteRegByte(_ubase8 fid,_ubase8 reg_addr,_ubase8 data);
_ubase8 i2cReadbyte(_ubase8 fid);
_ubase8 i2cReadRegByte(_ubase8 fid,_ubase8 reg_addr);

#ifdef __cplusplus
}
#endif

#endif //__I2C_H__