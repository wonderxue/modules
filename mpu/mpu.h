#ifndef __MPU__
#define __MPU__

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#include "main.h"

#define _mpu_Adress 0x68

struct mpu_Read
{
    unsigned char ACCEL_XOUT;
    unsigned char ACCEL_YOUT;
    unsigned char ACCEL_ZOUT;

    unsigned char TEMP_OUT;

    unsigned char GYRO_XOUT;
    unsigned char GYRO_YOUT;
    unsigned char GYRO_ZOUT;
};

extern struct mpu_Read mpu_Read;

void mpuInit(void);
short mpuReadData(unsigned char reg_address);

#ifdef __cplusplus
}
#endif

#endif //__MPU__