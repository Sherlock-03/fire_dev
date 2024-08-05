/*
    Include.h

    Include file for Application
*/

/*
    modification history
    --------------------
    01a, 09May24, Jasper Created
*/

#ifndef __INCLUDE_H
#define __INCLUDE_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
/* Std C */
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* RTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "cmsis_os.h"

/* HAL */
#include <stm32f1xx_hal.h>

/* Type & config */
#include "config.h"

/* Bsp */
#include "main.h"
#include "gpio.h"
#include "dma.h"
#include "usart.h"

/* library */
#include "lib/debug/lib_debug.h"
#include "lib/type/lib_type.h"
#include "lib/uart/lib_uart.h"
#include "lib/cli/lib_cli.h"
#include "lib/i2c/lib_i2c.h"
#include "lib/delay/lib_delay_us.h"
#include "lib/led/led_breath.h"
#include "drv/mpu6050/drv_mpu6050.h"
#include "lib/gyro/gyro.h"
#include "lib/capbutn/capbutn.h"
#include "lib/lamp/lamp.h"

//#include "lib/memory/lib_mem.h"

/* driver moudle */
//#include "drv/humiture/drv_aht30.h"
//#include "drv/rtc/drv_rtc_ds1338.h"
//#include "drv/rtc/drv_rtc.h"
//#include "drv/screen/drv_screen.h"
//#include "drv/screen/drv_dwin01.h"
//#include "drv/wifi/drv_wifi.h"
//#include "drv/wifi/drv_mhcwb8g.h"

/* application */
#include "app/arm_application/define.h"
#include "app/arm_application/user/app.h"
#include "app/arm_application/user/sys.h"
#include "app/arm_application/user/cli.h"

//#include "app/arm_application/user/drv/led.h"
//#include "app/arm_application/user/drv/fan.h"
//#include "app/arm_application/user/drv/rtc_time.h"
//#include "app/arm_application/user/drv/mem.h"
//#include "app/arm_application/user/drv/data.h"

#if 0
#include "debug/debug.h"
#include "Gpio/Gpio.h"
#include "Mem/Mem.h"
#include "Mem/MemFram.h"
#include "Mqtt/Mqtt.h"
#include "Net/Net.h"
#include "Prot/Prot.h"
#include "Rbuf/Rbuf.h"
#include "Rtc/Rtc.h"
#include "Uart/Uart.h"
#include "Wdog/Wdog.h"

/* Bsp library */
#include "BspGpio.h"
#include "BspSpi.h"
#include "BspUart.h"
#include "BspTim.h"
#include "BspI2C.h"

/* User application */
#include "User/_Type.h"
#include "User/_Config.h"
#include "User/_Include.h"
#include "User/Drv/Adc.h"
#include "User/Drv/Can.h"
#include "User/Drv/Dac.h"
#include "User/Drv/Gpio.h"
#include "User/Drv/Mem.h"
#include "User/Drv/Net.h"
#include "User/Drv/Pwr.h"
#include "User/Drv/Pwr/Pwr1Prot.h"
#include "User/Drv/Pwr/Pwr2Prot.h"
#include "User/Drv/Stc.h"
#include "User/Drv/Time.h"
#include "User/Cli.h"
#include "User/Com.h"
#include "User/Data.h"
#include "User/Sys.h"
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCLUDE_H */
