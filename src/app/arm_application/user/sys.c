/*
    sys.c

    Implementation File For The Whole Project
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 18May24, Jasper Created
*/

#include "app/arm_application/include.h"

/* Debug config */
#if SYS_DEBUG || 1
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* SYS_DEBUG */
#if SYS_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* SYS_ASSERT */

#define LIGHT_ID 2
#define LIGHT_SW_ID 1
#define LIGHT_BR_ID 2
#define LIGHT_CT_ID 3

#define FAN_ID 4
#define FAN_ON_OFF_ID 1
#define FAN_LEVEL_ID 2

#define CTTOPERENT(a)  (a - 2700) * 100 / 3000   /* 2700 - 5700  -> 0 - 100*/

/* global variable */
uint16_t g_previous_led_brightness = 0, g_previous_led_color_temperature = 0;

/* system task moudle */
//#define SYS_TASK_STACK_SIZE 128
//static StackType_t sys_task_stack[SYS_TASK_STACK_SIZE];
//static StaticTask_t sys_task_ctrl_block;
// TaskHandle_t sys_task_handle = NULL; /* 动态创建有问题，会卡死 */

/* Forward functions */
static void sys_task(void *parameter);

/* Functions */
status_t sys_init(void)
{
    xTaskCreate(sys_task, "sys_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);

    return status_ok;
}

static void sys_task(void *parameter)
{

  
    while (1)
    {
        
        osDelay(SYS_TASK_DELAY);
    }
}





