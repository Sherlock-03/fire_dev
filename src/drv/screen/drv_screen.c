/*
    drv_screen.c

    Implementation File For The screen moudle
*/

/* Copyright 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 23May24, Jasper Created
*/

#include "stm32f1xx_hal.h"
#include "lib/type/lib_type.h"
#include "drv/screen/drv_screen.h"
#include "drv/screen/drv_dwin01.h"
#include "lib/debug/lib_debug.h"

/* Debug config */
#if SCREEN_DEBUG || 1
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* SCREEN_DEBUG */
#if SCREEN_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* SCREEN_ASSERT */



status_t screen_init(screen_id_t screen_id, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_rx, DMA_HandleTypeDef *hdma_tx)
{
    switch (screen_id)
    {
    case dwin01:
        dwin01_init(huart, hdma_rx, hdma_tx);
        break;
    
    default:
        break;
    }
    return status_ok;
}