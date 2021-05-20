#ifndef __SPI_H__
#define __SPI_H__

//硬件配置
#define _spi_SDI
#define _spi_SDO
#define _spi_SCLK

enum spiSelectPin
{
    //多个CS pin时需要在此添加枚举值
    spi_CS_0=0,
    spi_CS_1,
    spi_CS_2,
};

enum spiMode
{
    /*  
    Mode0:
    Mode1:
    Mode2:
    Mode3:
    */
    spi_Mode_0=0,
    spi_Mode_1,
    spi_Mode_2,
    spi_Mode_3
};
//功能定义
unsigned char spiBegin(enum spiSelectPin spi_CS);
unsigned char spiDataTransfer(unsigned char fd,unsigned char data,enum spiMode spi_Mode);

#endif //__SPI_H__