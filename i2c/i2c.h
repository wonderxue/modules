#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "main.h"
//硬件配置
#define _i2c_SDA     13
#define _i2c_SCL     12
#define _i2c_SCL_L   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,RESET)
#define _i2c_SCL_H   HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,SET)
#define _i2c_SDA_L   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,RESET)
#define _i2c_SDA_H   HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,SET)
#define _i2c_SDA_In  SDAIn()
#define _i2c_SDA_Out SDAOut()
#define _i2c_SCL_Out SCLOut()
#define _i2c_SDA_Read HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin)
#define _i2c_Delay(x) delay_us(x)
extern void delay_us(int us);
//功能定义
unsigned char i2cBegin(unsigned short dev_addr);
void i2cSetTimeOut(int count);
_Bool i2cWriteByte(unsigned char fid,unsigned char data);
_Bool i2cWriteRegByte(unsigned char fid,unsigned char reg_addr,unsigned char data);
unsigned char i2cReadbyte(unsigned char fid);
unsigned char i2cReadRegByte(unsigned char fid,unsigned char reg_addr);

#ifdef __cplusplus
}
#endif

#endif //__I2C_H__