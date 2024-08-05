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
#ifndef __DRV_WIFI_H
#define __DRV_WIFI_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "stm32f1xx_hal.h"
#include "lib/type/lib_type.h"

    typedef enum
    {
        mhcwb8g = 0
    } wifi_id_t;

    status_t wifi_init(wifi_id_t wifi_id, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_rx, DMA_HandleTypeDef *hdma_tx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_WIFI_H */
