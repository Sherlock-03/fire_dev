#include "stm32f1xx_hal.h"
#include "lib/capbutn/capbutn.h"
#include "lib/type/lib_type.h"
#include "tim.h"
#include "freeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "lib/debug/lib_debug.h"

#if CAPBUTN_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* CAPBUTN */




/* Forward functions */
static void capbutn_init_task(void *parameter);


status_t capbutn_init(void)
{
    HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);
//    status_t status = ir_get_value();
//    if (status != status_ok) {
//        TRACE("IR initialization failed!\r\n");
//        return status_err;
//    }

    
    xTaskCreate(capbutn_init_task, "capbutn_init_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    TRACE("capbutn initialized successfully\r\n");
    return status_ok;
}

static void capbutn_init_task(void *parameter)
{
    
    
    while (1)
    {
        capbutn_get_value();
        osDelay(100);
    }
}

