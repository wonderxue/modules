#include "spi.h"
extern void logReport(_ubase8 loglevel,_base8 *file,_base8 *function, _base8 *info);
struct spiMode spiMode = {0, 1, 2, 3};
_ubase8 _spi_FrequencyPeriod = 1;
_ubase8 buffOut[8], buffIn[8];
enum _spi_CS_Status
{
    _spi_UnSelect = 0,
    _spi_Select
};
void spiSetFrequency(_ubase8 delayPeriod)
{
    _spi_FrequencyPeriod = delayPeriod;
}
void _spi_Error(_base8 *code)
{
    ErrorReport("--SPI--", code);
}
void _spiSelectPin(_ubase8 spiSelectPin, enum _spi_CS_Status spi_CS_Status)
{
    if (spiSelectPin == 0) //用于产生时钟周期，并不传输数据
        return;
    _spi_PinMode(spiSelectPin, _gpio_OUT);
    if (spi_CS_Status==_spi_Select)
        _spi_PinWrite(spiSelectPin, _gpio_LOW);
    else
        _spi_PinWrite(spiSelectPin, _gpio_HIGH);
}

_ubase8 spiRegist(_ubase8 spiSelectPin)
{
    _spi_SDI_In;
    _spi_SDO_Out;
    _spi_SCLK_Out;
    _spiSelectPin(spiSelectPin,_spi_UnSelect);
    return spiSelectPin;
}
void _spi_TransferModeByte0(_ubase8 fd, _ubase8 byteNum)
{
    _ubase8 i, j;
    _spi_SCLK_L;
    _spiSelectPin(fd, _spi_Select);
    for (j = 0; j < byteNum; j++)
    {
        for (i = 0; i < 8; i++)
        {
            if (buffIn[j] & 0x80)
                _spi_SDO_H;
            else
                _spi_SDO_L;
            buffIn[j] <<= 1;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_H;
            buffOut[j] <<= 1;
            if (_spi_SDI_Read)
                buffOut[j]++;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_L;
        }
    }
    _spiSelectPin(fd, _spi_UnSelect);
}

void _spi_TransferModeByte1(_ubase8 fd, _ubase8 byteNum)
{
    _ubase8 i, j;
    _spi_SCLK_L;
    _spiSelectPin(fd, _spi_Select);
    for (j = 0; j < byteNum; j++)
    {
        for (i = 0; i < 8; i++)
        {
            _spi_SCLK_H;
            if (buffIn[j] & 0x80)
                _spi_SDO_H;
            else
                _spi_SDO_L;
            buffIn[j] <<= 1;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_L;
            buffOut[j] <<= 1;
            if (_spi_SDI_Read)
                buffOut[j]++;
            _spi_DelayUs(_spi_FrequencyPeriod);
        }
    }
    _spiSelectPin(fd, _spi_UnSelect);
}

void _spi_TransferModeByte2(_ubase8 fd, _ubase8 byteNum)
{
    _ubase8 i, j;
    _spi_SCLK_H;
    _spiSelectPin(fd, _spi_Select);
    for (j = 0; j < byteNum; j++)
    {
        for (i = 0; i < 8; i++)
        {
            if (buffIn[j] & 0x80)
                _spi_SDO_H;
            else
                _spi_SDO_L;
            buffIn[j] <<= 1;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_L;
            buffOut[j] <<= 1;
            if (_spi_SDI_Read)
                buffOut[j]++;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_H;
        }
    }
    _spiSelectPin(fd, _spi_UnSelect);
}
void _spi_TransferModeByte3(_ubase8 fd, _ubase8 byteNum)
{
    _ubase8 i, j;
    _spi_SCLK_H;
    _spiSelectPin(fd, _spi_Select);
    for (j = 0; j < byteNum; j++)
    {
        for (i = 0; i < 8; i++)
        {
            _spi_SCLK_L;
            if (buffIn[j] & 0x80)
                _spi_SDO_H;
            else
                _spi_SDO_L;
            buffIn[j] <<= 1;
            _spi_DelayUs(_spi_FrequencyPeriod);
            _spi_SCLK_H;
            buffOut[j] <<= 1;
            if (_spi_SDI_Read)
                buffOut[j]++;
            _spi_DelayUs(_spi_FrequencyPeriod);
        }
    }
    _spiSelectPin(fd, _spi_UnSelect);
}
_ubase8 *spiMultiByteTransfer(_ubase8 fd, const _ubase8 *data, _ubase8 byteNum, _ubase8 spiMode)
{
    if (byteNum > 8)
    {
        _spi_Error("byteNum oversize (byteNum<=8)");
        return NULL;
    }
    //将源数据拷贝，避免通过指针更改
    memcpy(buffIn, data, byteNum);
    switch (spiMode)
    {
    case 0:
        _spi_TransferModeByte0(fd, byteNum);
        break;
    case 1:
        _spi_TransferModeByte1(fd, byteNum);
        break;
    case 2:
        _spi_TransferModeByte2(fd, byteNum);
        break;
    case 3:
        _spi_TransferModeByte3(fd, byteNum);
        break;
    default:
        _spi_Error("spiMode Error");
        return NULL;
        break;
    }
    return buffOut;
}
