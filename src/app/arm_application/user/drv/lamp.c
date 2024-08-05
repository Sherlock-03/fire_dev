#include "app/arm_application/include.h"

#if LAMP_DEBUG || 0
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* __LAMP__ */




/* Forward functions */
static void lamp_task(void *parameter);


status_t lamp_init(void)
{
    led_init();
    xTaskCreate(lamp_task, "lamp_task", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    TRACE("lamp initialized successfully\r\n");
    return status_ok;
}

static void lamp_task(void *parameter)
{
    while (1)
    {
        osDelay(100);
    }
}
