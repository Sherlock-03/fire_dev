/*
    lib_delay_us.c

    Implementation file for delay moudle
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 18May24, Jasper Created
*/

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "app/arm_application/config.h"

/* Debug config */
#if DELAY_US_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* DELAY_US_DEBUG */
#if DELAY_US_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* DELAY_US_ASSERT */

#if SORTWARE_I2C_ENABLE

void sys_tick_init(void)
{
    // 配置 SysTick 以微秒为单位计时
    SysTick->LOAD = (SystemCoreClock / 1000000) - 1;  // 每 1 微秒中断一次
    SysTick->VAL = 0;  // 清零当前计数值
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;  // 使能 SysTick
}

void delay_us(uint32_t us)
{
    // 禁用任务调度
    vTaskSuspendAll();

    // 读取当前计数值
    uint32_t start = SysTick->VAL;
    // 计算目标计数值，SysTick 是递减计数器
    uint32_t ticks = us * (SystemCoreClock / 1000000);

    // 处理 SysTick 计数器溢出的情况
    if (start < ticks)
    {
        // 如果 start 比 ticks 小，等待 SysTick 溢出
        while (SysTick->VAL <= start);
        start += (SysTick->LOAD + 1);
    }

    // 等待延时结束
    while ((start - SysTick->VAL) < ticks);

    // 恢复任务调度
    xTaskResumeAll();
}

#endif
