/*
    drv_dwin01.h

    Implementation File For The dwin01 moudle
*/

/* Copyright 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 23May24, Jasper Created
*/
#ifndef __DRV_DWIN01_H
#define __DRV_DWIN01_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "FreeRTOS.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "lib/type/lib_type.h"
#include "lib/uart/lib_uart.h"

    /* system */
    enum {
        SET_BRIGHTNESS      = 0x0082
    };

    /* user */
    enum {
        SET_LED_BR_ADDR      = 0x1001,
        SET_LED_CT_ADDR      = 0x1002,
        SET_LED_ONOFF_ADDR   = 0x1003,
        SET_FAN_ONOFF_ADDR   = 0x1004,
        SET_FAN_LEVEL_ADDR   = 0x1005
    };




    // 定义消息结构体，用于传递数据
    #define RX_BUFFER_SIZE 10
    typedef struct {
        uint8_t data[RX_BUFFER_SIZE];
        uint8_t length;
    } Message;

    // 声明消息队列句柄
    extern QueueHandle_t xQueue;

    extern uart_ctrl_t g_screen_ctrl;
    status_t dwin01_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_rx, DMA_HandleTypeDef *hdma_tx);
    static uint8_t *prvParseHexStr(const char *pcStr, uint8_t *pucLength);
    status_t refresh_screen(uint16_t address, uint8_t value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_DWIN01_H */
