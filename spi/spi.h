#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

//硬件配置
#define _spi_SDI
#define _spi_SDO
#define _spi_SCLK

#define _spi_SDI_In
#define _spi_SDO_Out
#define _spi_SCLK_Out

#define _spi_SDI_Read
#define _spi_SDO_H
#define _spi_SDO_L
#define _spi_SCLK_H
#define _spi_SCLK_L

#define _spi_Delay(x) 
struct spiSelectPin
{
    //多个CS pin时需要在此添加枚举值
    unsigned char spi_CS_0;
    unsigned char spi_CS_1;
    unsigned char spi_CS_2;
};

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
    unsigned char spi_Mode_0;
    unsigned char spi_Mode_1;
    unsigned char spi_Mode_2;
    unsigned char spi_Mode_3;
};

extern struct spiSelectPin spiSelectPin;
extern struct spiMode spiMode;
//功能定义
unsigned char spiBegin(unsigned char spiSelectPin);
unsigned char spiDataTransfer(unsigned char fd,unsigned char data,unsigned char spiMode);

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__