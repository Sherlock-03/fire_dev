/*
    drv_dmg40960f040_01wtc.h

    Implementation File For The dmg40960f040_01wtc moudle
*/

/* Copyright 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 23May24, Jasper Created
*/
#ifndef __DRV_MHCWB8G_H
#define __DRV_MHCWB8G_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "FreeRTOS.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "lib/type/lib_type.h"
#include "lib/uart/lib_uart.h"

    // 定义消息结构体，用于传递数据
    #define WIFI_RX_BUFFER_SIZE 40
    typedef struct {
        uint8_t data[WIFI_RX_BUFFER_SIZE];
        uint8_t length;
    } wifi_msg_t;

    extern uart_ctrl_t g_wifi_ctrl;
    extern QueueHandle_t wifi_uart_queue;

    status_t mhcwb8g_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_rx, DMA_HandleTypeDef *hdma_tx);
    status_t wifi_send_cmd(const char *cmd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_MHCWB8G_H */
