#include "sd_spi.h"
//unsigned char _sd_fd;//HAL库不用
extern void ErrorReport(char *source, char *code);
unsigned int _sd_TimeOut = 500;
void _sd_Error(char *code)
{
  ErrorReport("--SD--  ", code);
}
void _sd_SpiSpeedSet(_Bool Speed)
{
  if(Speed==_sd_Spi_Speed_HIGH)
  {
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  }
  else
  {
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  }
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}
void _sd_SpiWriteRead(unsigned char *pIn, unsigned char *pOut, unsigned char ByteNum)
{
  HAL_SPI_TransmitReceive(&hspi1, pIn, pOut, ByteNum, ByteNum * 500);
}
unsigned char _sd_SendCMD(unsigned char ucmd, unsigned char *arg, unsigned char crc)
{
  unsigned char  res, tmp = 0xff, cmd[6];
  int i=0;
  *cmd = ucmd | 0x40;
  memcpy(cmd + 1, arg, 4);
  *(cmd + 5) = (crc << 1) + 1;
  _sd_CS_Set;
  _sd_SpiWriteRead(&tmp, &tmp, 1);
  _sd_CS_Reset;
  _sd_SpiWriteRead(cmd, cmd, 6);
  i = 0;
  do
  {
    /* code */
    _sd_SpiWriteRead(&tmp, &res, 1);
  } while ((res == MSD_RESPONSE_FAILURE) && (++i < _sd_TimeOut) /* condition */);
  if (i == _sd_TimeOut)
  {
    _sd_Error("Cmd time out");
  }
  _sd_CS_Set;
  return res;
}

_Bool _sd_Reset()
{
  unsigned char res, tmp = 0xff, arg[4] = {0, 0, 0, 0};
  int i=0;
  for (i = 0; i < 0x2f; i++)
    _sd_SpiWriteRead(&tmp, &tmp, 1);
  i = 0;
  do
  {
    /* code */
    res = _sd_SendCMD(CMD0, arg, CMD0_CRC);
  } while ((res != MSD_IN_IDLE_STATE) && (++i < _sd_TimeOut));
  if (i == _sd_TimeOut)
  {
    _sd_Error("Reset time out");
    return _sd_False;
  }
  return _sd_True;
}

unsigned char _sd_Init()
{
  unsigned char res, out[4], arg[4] = {0, 0, 0x01, 0xaa};
  int i=0;
  //判断是否为SD2.0
  res = _sd_SendCMD(CMD8, arg, CMD8_CRC);
  i = 0;
  arg[2] = 0;
  arg[3] = 0;
  out[1] = 0xff;
  if (res == RES_SD_V2)
  {
    //接收剩余数据
    _sd_CS_Reset;
    _sd_SpiWriteRead(arg, out, 4);
    _sd_CS_Set;
    if (out[2] != 0x01)
    {
      _sd_Error("SD_V2 identified but voltage not satisfied");
    }
    if (out[3] != 0xaa)
    {
      _sd_Error("SD_V2 identified but return data not correct");
    }
    arg[0] = 0x40;
    _sd_CS_Reset;
    _sd_SpiWriteRead(arg, out, 1);
    _sd_CS_Set;
    do
    {
      /* code */
      out[0] = _sd_SendCMD(CMD55, arg, Fake_CRC);
      if (out[0] != MSD_IN_IDLE_STATE)
        _sd_Error("SD_V2 CMD55 response error");
      out[1] = _sd_SendCMD(ACMD41, arg, Fake_CRC);
    } while ((out[1] != MSD_RESPONSE_NO_ERROR) && (++i < _sd_TimeOut));
    if (i == _sd_TimeOut)
    {
      _sd_Error("SD_V2 identified but ACMD41 response time out");
      return SD_TYPE_ERR;
    }

    //获取OCR
    arg[0] = 0;
    arg[1] = 0;
    arg[2] = 0;
    arg[3] = 0;
    res = _sd_SendCMD(CMD58, arg, Fake_CRC);
    if (res != MSD_RESPONSE_NO_ERROR)
    {
      _sd_Error("SD_V2 identified but get OCR info error");
      return SD_TYPE_ERR;
    }
    _sd_CS_Reset;
    _sd_SpiWriteRead(arg, out, 4);
    _sd_CS_Set;
    if (out[0] & 0x40)
      return SD_TYPE_V2HC;
    else
      return SD_TYPE_V2;
  }
  else if (res == RES_SD_V1)
  {
    //SD V1
    do
    {
      /* code */
      out[0] = _sd_SendCMD(CMD55, arg, Fake_CRC);
      if (out[0] != MSD_IN_IDLE_STATE)
        _sd_Error("SD_V1 CMD55 response error");
      else
        out[1] = _sd_SendCMD(ACMD41, arg, Fake_CRC);
    } while ((out[1] != MSD_RESPONSE_NO_ERROR) && (++i < _sd_TimeOut));
    if (i == _sd_TimeOut)
    {
      //判断是否MMC
      i = 0;
      do
      {
        /* code */
        res = _sd_SendCMD(CMD1, arg, Fake_CRC);
      } while ((res != MSD_RESPONSE_NO_ERROR) && (++i < _sd_TimeOut));
      if (i == _sd_TimeOut)
      {
        _sd_Error("MMC initial timeout or sd unstable");
        return SD_TYPE_ERR;
      }
      res = _sd_SendCMD(CMD59, arg, Fake_CRC);
      if (res != MSD_RESPONSE_NO_ERROR)
      {
        _sd_Error("MMC turn CRC check off error");
      }
      arg[2] = 2; // sector size=512
      res = _sd_SendCMD(CMD16, arg, Fake_CRC);
      if (res != MSD_RESPONSE_NO_ERROR)
      {
        _sd_Error("MMC set sector size error");
      }
      return SD_TYPE_MMC;
    }
    return SD_TYPE_V1;
  }
  return SD_TYPE_ERR;
}
unsigned char  sdInit()
{
  unsigned char res;
  _sd_SpiSpeedSet(_sd_Spi_Speed_LOW);
  _sd_Reset();
  res = _sd_Init();
  _sd_SpiSpeedSet(_sd_Spi_Speed_HIGH);
  return res;
}
unsigned char sdGetCID(unsigned char *cid)
{
  unsigned char res,arg[4]={0,0,0,0};
  res=_sd_SendCMD(CMD10,arg,Fake_CRC);
  if(res!=MSD_RESPONSE_NO_ERROR)
  {
    _sd_Error("Get CID error");
    return _sd_False;
  }
  _sd_CS_Reset;
  _sd_SpiWriteRead(cid,cid,16);
  _sd_CS_Set;
  return _sd_True;
}
unsigned int sdGetCapacityKB()
{
  unsigned int Capacity;
  unsigned char res,acsd[16],csd[16]={0,0,0,0},C_SIZE_MULT,READ_BL_LEN;
  unsigned short C_SIZE;
  res=_sd_SendCMD(CMD9,csd,Fake_CRC);
  if(res!=MSD_RESPONSE_NO_ERROR)
  {
    _sd_Error("Get CSD error");
    return _sd_False;
  }
  _sd_CS_Reset;
  _sd_SpiWriteRead(acsd,csd,16);
  _sd_CS_Set;
  if(csd[0]&0xc0==0x40)
  {
    //v2
    _sd_Error("----V2------");
    C_SIZE=csd[9]+((unsigned int)csd[8]<<8)+((unsigned int)(csd[7]&63)<<16)+1;
    Capacity=C_SIZE<<9;
  }
  else
  {
    //v1
    _sd_Error("----V1------");
    C_SIZE=(csd[8]>>6)+((unsigned short)csd[7]<<2)+((unsigned short)(csd[6]&3)<<10);
    C_SIZE_MULT=((csd[10]&128)>>7)+((csd[9]&3)<<1);
    READ_BL_LEN=csd[5]&15;
    Capacity=(C_SIZE+1)<<(C_SIZE_MULT+2+READ_BL_LEN-10);
  }
  return Capacity;
}