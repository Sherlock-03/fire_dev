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
#include "lib/gyro/gyro.h"

#if MPU6050_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* MPU6050_DEBUG */

mpu6050_data mpu6050data;

/* Forward functions */
static void mpu6050_init_task(void *parameter);

/* Functions */
status_t gyro_init(void)
{
    status_t status = mpu6050_ready();
    if (status != status_ok) {
        TRACE("MPU6050 initialization failed!\r\n");
        return status_err;
    }

    TRACE("MPU6050 initialized successfully\r\n");
    xTaskCreate(mpu6050_init_task, "mpu6050_init_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

    return status_ok;
}

static void mpu6050_init_task(void *parameter)
{
    while (1)
    {
        mpu6050_read_data(&mpu6050data);
        osDelay(10);
    }
}
