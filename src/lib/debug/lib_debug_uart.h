/*
    DebugUart.h

    Head File for Debug Uart Module
*/

/* Copyright 2019 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 10Sep18, Karl Created
    01b, 15Nov18, Karl Modified
    01c, 15Jul19, Karl Reconstructured Debug module
*/

#ifndef __DEBUG_UART_H__
#define __DEBUG_UART_H__

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */

/* Includes */
#include <stdint.h>
#include <stm32f1xx_hal.h>
#include "lib/type/lib_type.h"
#include "lib/debug/lib_debug_config.h"

    /* Functions */
    status_t debug_uart_init(void);
    status_t debug_uart_term(void);
    status_t debug_uart_config(UART_HandleTypeDef *pxUart);

    status_t DebugUartPrintf(char *cFormat, ...);
    status_t DebugUartPrintfDirect(char *cStr, uint16_t usLength);

#if DEBUG_UART_ENABLE_MSP
    void HAL_UART_MspInit(UART_HandleTypeDef *pxUartHandle);
    void HAL_UART_MspDeInit(UART_HandleTypeDef *pxUartHandle);
#endif /* DEBUG_UART_ENABLE_MSP */

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*__DEBUG_UART_H__*/
