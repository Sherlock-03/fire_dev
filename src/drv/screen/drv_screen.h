/*
    drv_screen.h

    Implementation File For The drv_screen moudle
*/

/* Copyright 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 23May24, Jasper Created
*/
#ifndef __DRV_SCREEN_H
#define __DRV_SCREEN_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "lib/type/lib_type.h"
#include "stm32f1xx_hal.h"

    typedef enum
    {
        dwin01 = 0
    } screen_id_t;

    status_t screen_init(screen_id_t screen_id, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_rx, DMA_HandleTypeDef *hdma_tx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_SCREEN_H */
