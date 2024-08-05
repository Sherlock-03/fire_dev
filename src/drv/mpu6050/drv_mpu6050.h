#ifndef __DRV_MPU6050__
#define __DRV_MPU6050__

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/type/lib_type.h"

#define MPU6050_DEBUG 1

#define MPU6050_ADDR         0x68       // MPU6050 I2C 地址（0x68 左移 1 位以匹配 HAL 库的 7 位地址格式）
#define MPU6050_WHO_AM_I     0x75       // WHO_AM_I 寄存器地址
#define MPU6050_PWR_MGMT_1   0x6B       // 电源管理寄存器地址
#define MPU6050_SMPLRT_DIV   0x19       // 采样率分频寄存器地址
#define MPU6050_CONFIG       0x1A       // 配置寄存器地址
#define MPU6050_GYRO_CONFIG  0x1B       // 陀螺仪配置寄存器地址
#define MPU6050_ACCEL_CONFIG 0x1C       // 加速度计配置寄存器地址
#define MPU6050_INT_ENABLE   0x38       // 中断使能寄存器地址

typedef struct {
    int16_t Accel_X;
    int16_t Accel_Y;
    int16_t Accel_Z;
    int16_t Gyro_X;
    int16_t Gyro_Y;
    int16_t Gyro_Z;
}mpu6050_data;


status_t mpu6050_ready(void);
status_t mpu6050_read_data(mpu6050_data *data);
status_t mpu6050_init(void);

#ifdef __cplusplus
}
#endif
#endif /*__DRV_MPU6050__*/

