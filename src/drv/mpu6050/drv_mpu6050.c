#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "usart.h"
#include "lib/i2c/lib_i2c.h"
#include "lib/debug/lib_debug.h"
#include "lib/uart/lib_uart.h"
#include "freeRTOS.h"
#include "task.h"
#include "drv/mpu6050/drv_mpu6050.h"
#include "lib/type/lib_type.h"

#if MPU6050_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* MPU6050_DEBUG */

    // 初始化MPU6050
status_t mpu6050_ready(void)
{
    osDelay(100);
    uint8_t data;

    // 解除休眠模式
    data = 0x00;
    if (i2c_write_register(MPU6050_ADDR, MPU6050_PWR_MGMT_1, &data, 1) != status_ok) {
        TRACE("sleep\n");
        return status_err;
    }

    // 设置采样率分频
    data = 0x07;
    if (i2c_write_register(MPU6050_ADDR, MPU6050_SMPLRT_DIV, &data, 1) != status_ok) {
        TRACE("freq\r\n");
        return status_err;
    }

    // 配置低通滤波器
    data = 0x06;
    if (i2c_write_register(MPU6050_ADDR, MPU6050_CONFIG, &data, 1) != status_ok) {
        TRACE("lvboqi\r\n");
        return status_err;
    }

    // 设置陀螺仪量程
    data = 0x08;
    if (i2c_write_register(MPU6050_ADDR, MPU6050_GYRO_CONFIG, &data, 1) != status_ok) {
        TRACE("tuoluyi\r\n");
        return status_err;
    }

    // 设置加速度计量程
    data = 0x00;
    if (i2c_write_register(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, &data, 1) != status_ok) {
        TRACE("range\r\n");
        return status_err;
    }

    TRACE("MPU6050 is ready\r\n");
    return status_ok;
}

// 读取MPU6050模块的数据
status_t mpu6050_read_data(mpu6050_data *data)
{
    uint8_t buffer[14];

    // 读取加速度和陀螺仪数据寄存器
    status_t status = i2c_read_register(MPU6050_ADDR, 0x3B, buffer, 14);
    if (status != status_ok) {
        TRACE("Failed to read MPU6050 data\r\n");
        return status;
    }

    data->Accel_X = (int16_t)((buffer[0] << 8) | buffer[1]);
    data->Accel_Y = (int16_t)((buffer[2] << 8) | buffer[3]);
    data->Accel_Z = (int16_t)((buffer[4] << 8) | buffer[5]);
    data->Gyro_X  = (int16_t)((buffer[8] << 8) | buffer[9]);
    data->Gyro_Y  = (int16_t)((buffer[10] << 8) | buffer[11]);
    data->Gyro_Z  = (int16_t)((buffer[12] << 8) | buffer[13]);

    TRACE("Accel: X=%5d, Y=%5d, Z=%5d\nGyro: X=%5d, Y=%5d, Z=%5d\r\n\n\n",
          data->Accel_X, data->Accel_Y, data->Accel_Z,
          data->Gyro_X, data->Gyro_Y, data->Gyro_Z);

    osDelay(1000); // 每秒读取并发送一次数据

    return status_ok;
}

