#include "sd_spi.h"
unsigned char _sd_fd;
extern enum _spi_CS_Status;
extern void _spiSelectPin(unsigned char spiSelectPin, enum _spi_CS_Status spi_CS_Status);
extern void ErrorReport(char *source, char *code);
unsigned char _sd_TimeOut = 200;
void _sd_Error(char *code)
{
    ErrorReport("--SD--", code);
}
unsigned char _sd_SendCMD(unsigned char CMD, unsigned int arg, unsigned char CRC)
{
    unsigned short data;
    unsigned char res, i = 0;
    data=(((CMD|0x40)<<8)+(arg>>24);
    spiWordTransfer(_sd_fd,data,spiMode.spi_Mode_0);
    data=arg>>8;
    spiWordTransfer(_sd_fd,data,spiMode.spi_Mode_0);
    data=(arg<<8)+(CRC<<1)+1;
    spiWordTransfer(_sd_fd,data,spiMode.spi_Mode_0);
    do
    {
        /* code */
        res = spiByteTransfer(_sd_fd, 0xff, spiMode.spi_Mode_0);
        i++;
    } while ((res|0x80)&&(i<_sd_TimeOut));
    if(i==_sd_TimeOut)
    _sd_Error("Wait CMD Response TimeOut");
    return res;
}
_Bool _sd_Reset()
{
    unsigned char res;
    _spiSelectPin(_sd_fd, _spi_UnSelect);
    for (i = 0; i < 10; i++)
        spiByteTransfer(0, 0xff, spiMode.spi_Mode_0);
    res = _sd_SendCMD(CMD0, 0x00, 0x4a);
    if (res == 0x01)
    {
        spiByteTransfer(0, 0xff, spiMode.spi_Mode_0);
        return _sd_True;
    }
    _sd_Error("ReSet Error");
    return _sd_False;
}
unsigned int _sd_GetInfo()
{
    unsigned char res;
    unsigned int info = 0;
    res = _sd_SendCMD(CMD8, 0x1aa, 0x43);
    if (res == 0x01)
    {
        info = spiWordTransfer(_sd_fd, 0xffff, spiMode.spi_Mode_0);
        info = (info << 16) + spiWordTransfer(_sd_fd, 0xffff, spiMode.spi_Mode_0);
        spiByteTransfer(0, 0xff, spiMode.spi_Mode_0);
        return info;
    }
    _sd_Error("getInfo Error");
    return _sd_False;
}
unsigned char _sd_Init()
{
    unsigned char res, i=0;
    unsigned int info = 0;
    do
    {
        /* code */
        res = _sd_SendCMD(CMD55, 0x00, 0xff);
        if (res == 0x01)
        {
            res = _sd_SendCMD(ACMD41, 0x40000000, 0xff);
        }
        else
        _sd_Error("sd Init Error:CMD55");
        i++;
    } while ((res!=0)&&(i<_sd_TimeOut));
    if(i==_sd_TimeOut)
    _sd_Error("sd Init TimeOut");
    res=_sd_SendCMD(CMD58,0x00,0xff);
    if(res!=0)
    _sd_Error("sd Init CMD58 Erorr");
    info = spiWordTransfer(_sd_fd, 0xffff, spiMode.spi_Mode_0);
    info = (info << 16) + spiWordTransfer(_sd_fd, 0xffff, spiMode.spi_Mode_0);
    spiByteTransfer(0, 0xff, spiMode.spi_Mode_0);
    //todo
    //鉴别sd卡类型
}
void sdInit()
{
    unsigned char res;
    _sd_fd = spiRegist(_sd_CS);
    spiSetFrequency(100);
    _sd_Reset();
    res = _sd_SendCMD(CMD8, 0x00, 0xff);
    _sd_GetInfo();
    _sd_Init();
    spiSetFrequency(1);
}