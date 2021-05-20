#include "spi.h"
enum _spi_CS_Status
{
    _spi_UnSelect=0,
    _spi_Select
};
__attribute__((weak)) void _spiSelectPin(enum spiSelectPin spi_CS,enum _spi_CS_Status spi_CS_Status)
{
    #if 1
    #error please add code here to change the spi_CS_Pin status and change 1 to 0
    #endif
}

unsigned char spiRegist(enum spiSelectPin spi_CS)
{
    return spi_CS;
}

unsigned char spiDataTransfer(unsigned char fd,unsigned char data,enum _spiMode spiMode)
{
    _spiSelectPin(fd,_spi_Select);



    _spiSelectPin(fd,_spi_UnSelect);
    return 1;
}
