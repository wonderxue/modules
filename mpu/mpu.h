#ifndef __MPU__
#define __MPU__
#include "../module_conf.h"
#include "i2c.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void _time_delayMs(_ubase16 x);
#define _mpu_Adress 0x68
#define _mpu_DelayMs(x)  _time_delayMs(x)
struct mpu_Read
{
    _ubase8 ACCEL_XOUT;
    _ubase8 ACCEL_YOUT;
    _ubase8 ACCEL_ZOUT;

    _ubase8 TEMP_OUT;

    _ubase8 GYRO_XOUT;
    _ubase8 GYRO_YOUT;
    _ubase8 GYRO_ZOUT;
};

extern struct mpu_Read mpu_Read;

void mpuInit(void);
_base16 mpuReadData(_ubase8 reg_address);

#ifdef __cplusplus
}
#endif

#endif //__MPU__