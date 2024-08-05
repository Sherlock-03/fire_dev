#include "stm32f1xx_hal.h"
#include "lib/lamp/lamp.h"
#include "lib/type/lib_type.h"
#include "tim.h"
#include "freeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "lib/debug/lib_debug.h"

#if LAMP_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* __LAMP__ */




/* Forward functions */
static void lamp_init_task(void *parameter);


status_t lamp_init(void)
{
   
//    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
    
    xTaskCreate(lamp_init_task, "lamp_init_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    TRACE("lamp initialized successfully\r\n");
    return status_ok;
}

static void lamp_init_task(void *parameter)
{
     led_color();
    
    while (1)
    {
        
        osDelay(100);
    }
}
