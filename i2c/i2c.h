#ifndef __I2C_H__
#define __I2C_H__

//硬件配置
#define SDA     13
#define SCL     12
#define SCL_L   
#define SCL_H
#define SDA_L
#define SDA_H
#define SDA_In
#define SDA_Out
#define SDA_Read
#define i2cDelay(x) 

//功能定义
unsigned char begin(unsigned short dev_addr);
_Bool writeByte(unsigned char fid,unsigned char data);
_Bool writeRegByte(unsigned char fid,unsigned char reg_addr,unsigned char data);
unsigned char readbyte(unsigned char fid);
unsigned char readRegByte(unsigned char fid,unsigned char reg_addr);

#endif //__I2C_H__