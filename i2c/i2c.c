#include "i2c.h"
unsigned char timeOut = 200;
__weak void i2cError(unsigned char *code)
{
#warning redefine function i2cError may better
    while (1)
        ;
}
void start()
{
    SDA_Out;
    SDA_H;
    SCL_H;
    i2cDelay(5);
    SDA_L;
    i2cDelay(6);
    SCL_L;
}
void stop()
{
    SDA_Out;
    SCL_L;
    SDA_L;
    SCL_H;
    i2cDelay(6);
    SDA_H;
    i2cDelay(6);
}
void sendAck(_Bool ack) //低 应答
{
    SCL_L;
    SDA_Out;
    if (ack)
        SDA_H;
    else
        SDA_L;
    i2cDelay(2);
    SCL_H;
    i2cDelay(5);
    SCL_L;
}
_Bool waitAck()
{
    unsigned char tempTime = 0;
    SDA_In; //配置为上拉输入。
    SDA_H;  //主机释放数据总线，等待从机产生应答信号
    i2cDelay(1);
    SCL_H;
    i2cDelay(1);
    //等待从机对数据总线的操作。低电平代表应答
    while (SDA_Read)
    {
        tempTime++;
        //这个属于软件延时，不一定准确。
        if (tempTime > timeOut) //如果时间超时，没有应答就停止。
        {
            Stop();
            return 1; //没有响应的话返回1.
        }
    }
    SCL_L;
    return 0; //如果有响应的话就返回0.
}
_Bool write(unsigned char data)
{
    SDA_Out;
    SCL_L;
    i2cDelay(2);
    for (int i = 0; i < 8; i++) //从高位开始一位一位地传送
    {
        //发数据放到数据线上
        if ((data & 0x80) > 0) //当前的最高位为1
            SDA_H;             //拉高数据线
        else
            SDA_L;
        data << 1; //数据左移一位
        //开始发送数据
        SCL_H;
        i2cDelay(2);
        //上一个数据发送完毕，为下一个数据发送准备
        SCL_L;
        i2cDelay(2);
    }
    return waitAck();
}
unsigned char read(_Bool ack)
{
    unsigned char data; //接收到的数据
    SDA_In;
    for (int i = 0; i < 8; i++)
    {
        //数据准备
        SCL_L;
        i2cDelay(2);
        SCL_H;        //主机开始读数据，从机不能再改变数据了，即改变SDA的电平
        if (SDA_Read) //接收到的是1
            data++;
        data << 1;
        i2cDelay(1);
    }
    sendAck(ack);
    return data;
}
unsigned char begin(unsigned short dev_addr)
{
    return dev_addr;
}
_Bool writeByte(unsigned char fid, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    start();
    status = write(dev_addr);
    if (status)
    {
        stop();
        i2cError("write dev_addr error");
        return status;
    }
    status = write(data);
    if (status)
        i2cError("write data error");
    stop();
    return status;
}
_Bool writeRegByte(unsigned char fid, unsigned char reg_addr, unsigned char data)
{
    _Bool status;
    unsigned char dev_addr = fid << 1;
    start();
    status = write(dev_addr);
    if (status)
    {
        stop();
        i2cError("write dev_addr error");
        return status;
    }
    status = write(reg_addr);
    if (status)
    {
        stop();
        i2cError("write reg_addr error");
        return status;
    }
    status = write(data);
    if (status)
        i2cError("write data error");
    stop();
    return status;
}
unsigned char readbyte(unsigned char fid)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = fid << 1 + 1;
    start();
    status = write(dev_addr);
    if (status)
    {
        stop();
        i2cError("read dev_addr error");
        return status;
    }
    data = read(1);
    stop();
    return data;
}
unsigned char readRegByte(unsigned char fid, unsigned char reg_addr)
{
    _Bool status;
    unsigned char data;
    unsigned char dev_addr = fid << 1 + 1;
    start();
    status = write(dev_addr);
    if (status)
    {
        stop();
        i2cError("read dev_addr error");
        return status;
    }
    status = write(reg_addr);
    if (status)
    {
        stop();
        i2cError("read reg_addr error");
        return status;
    }
    data = read(1);
    stop();
    return data;
}
