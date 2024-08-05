/*
    lib_uart.c

    Implementation File for Uart Module
*/

/*
    modification history
    --------------------
    01a, 09May24, Jasper Created

*/

/* Includes */
#include <stdlib.h>
#include <string.h>
#include <cmsis_os.h>
#include "lib/uart/lib_uart.h"
#include "lib/debug/lib_debug.h"

#if UART_ENABLE

/* Pragmas */
#pragma diag_suppress 177 /* warning: #177-D: variable was declared but never referenced */
#pragma diag_suppress 188 /* warning: #188-D: enumerated type mixed with another type */

/* Debug config */
#if UART_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* UART_DEBUG */
#if UART_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* UART_ASSERT */

/* Local defines */
#define UART_GET_CTRL(handle) ((uart_ctrl_t *)(handle))

/* Local types */


/* Functions */
status_t uart_init(void)
{
    /* Do nothing */
    return status_ok;
}

status_t uart_terminal(void)
{
    /* Do nothing */
    return status_ok;
}

#if 0
uart_ctrl_t uart_create(void)
{
    uart_ctrl_t *uart_handle = NULL;
    uart_handle = (uart_ctrl_t *)pvPortMalloc(sizeof(uart_ctrl_t));
    ASSERT(NULL != uart_handle);
    if (uart_handle)
    {
        memset(uart_handle, 0, sizeof(uart_ctrl_t));
    }
    return (uart_ctrl_t)uart_handle;
}

status_t uart_delete(uart_ctrl_t *uart_handle)
{
    if (uart_handle)
    {
        vPortFree((void *)uart_handle);
    }
    return status_ok;
}
#endif

status_t uart_config_callback(uart_ctrl_t *uart_handle, uart_process_function_t process_rx_function, uart_isr_function_t uart_isr_function, uart_isr_function_t dma_rx_isr_function, uart_isr_function_t dma_tx_isr_function, void *isr_para)
{
    // // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);
    ASSERT(NULL != uart_handle);

    uart_handle->uart_isr_function = uart_isr_function;
    uart_handle->dma_rx_isr_function = dma_rx_isr_function;
    uart_handle->dma_tx_isr_function = dma_tx_isr_function;
    uart_handle->process_rx_function = process_rx_function;
    uart_handle->isr_para = isr_para;
    return status_ok;
}

status_t uart_config_handle(uart_ctrl_t *uart_handle, UART_HandleTypeDef *_huart, DMA_HandleTypeDef *_hdma_rx, DMA_HandleTypeDef *_hdma_tx)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    uart_handle->_huart = _huart;
    uart_handle->_hdma_rx = _hdma_rx;
    uart_handle->_hdma_tx = _hdma_tx;
    uart_handle->rx_length = 0;
    if (NULL != _huart)
    {
        __HAL_UART_ENABLE_IT(uart_handle->_huart, UART_IT_IDLE);
    }

    if (NULL != _hdma_rx)
    {
        //__HAL_UART_ENABLE_IT(uart_handle->_huart, UART_IT_IDLE);
        HAL_UART_Receive_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->rx_buffer), UART_RXBUF_SIZE);
        // HAL_UARTEx_ReceiveToIdle_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->rx_buffer), UART_RXBUF_SIZE);
    }
    else
    {
        //HAL_UART_Receive_IT(_huart, uart_handle->rx_buffer, UART_RXBUF_SIZE);
        __HAL_UART_ENABLE_IT(_huart, UART_IT_RXNE);
    }

    return status_ok;
}

status_t uart_start_it(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
    __HAL_UART_CLEAR_IDLEFLAG(uart_handle->_huart);
    __HAL_UART_ENABLE_IT(uart_handle->_huart, UART_IT_IDLE);
    /* Restart UART DMA receive */
    HAL_UART_Receive_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->rx_buffer), UART_RXBUF_SIZE);

    return status_ok;
}

status_t uart_stop_it(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
    /* Disable IDLE interrupt */
    __HAL_UART_DISABLE_IT(uart_handle->_huart, UART_IT_IDLE);
    /* Stop DMA transfer */
    HAL_UART_DMAStop(uart_handle->_huart);

    return status_ok;
}

status_t uart_dma_send(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t receive_length, uint16_t wait_ms)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != receive_buffer);
    ASSERT(NULL != uart_handle);
    HAL_UART_StateTypeDef state = HAL_UART_GetState(uart_handle->_huart) & HAL_UART_STATE_BUSY_TX;
    while ((state == HAL_UART_STATE_BUSY_TX) && wait_ms)
    {
        state = HAL_UART_GetState(uart_handle->_huart) & HAL_UART_STATE_BUSY_TX;
        wait_ms--;
        osDelay(1);
    }

    if (state != HAL_UART_STATE_BUSY_TX)
    {
        if (receive_length <= UART_TXBUF_SIZE)
        {
            memcpy(uart_handle->tx_buffer, receive_buffer, receive_length);
            if (HAL_OK == HAL_UART_Transmit_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->tx_buffer), receive_length))
            {
                return status_ok;
            }
            else
            {
                TRACE("UartDmaSend: send error\n");
                return status_err;
            }
        }
        else
        {
            TRACE("UartDmaSend: length error\n");
            return status_err;
        }
    }
    else
    {
        TRACE("UartDmaSend: busy error\n");
        return status_err;
    }
}

status_t uart_block_send(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t receive_length, uint16_t wait_ms)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != receive_buffer);
    ASSERT(NULL != uart_handle);
    HAL_UART_StateTypeDef state = HAL_UART_GetState(uart_handle->_huart) & HAL_UART_STATE_BUSY_TX;
    while (state == HAL_UART_STATE_BUSY_TX)
    {
        state = HAL_UART_GetState(uart_handle->_huart) & HAL_UART_STATE_BUSY_TX;
    }
    if (HAL_OK == HAL_UART_Transmit(uart_handle->_huart, (uint8_t *)receive_buffer, receive_length, wait_ms))
    {
        return status_ok;
    }
    else
    {
        return status_err;
    }
}

status_t uart_block_read(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t *preceive_length, uint16_t wait_ms)
{
    uint16_t n = 0;
    uint16_t usCnt = 0;
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);
    HAL_StatusTypeDef state;

    ASSERT(NULL != receive_buffer);
    ASSERT(NULL != uart_handle);
    usCnt = *preceive_length;
    for (n = 0; n < usCnt; n++)
    {
        while (HAL_UART_STATE_BUSY_RX == (HAL_UART_GetState(uart_handle->_huart) & HAL_UART_STATE_BUSY_RX))
        {
        };

        state = HAL_UART_Receive(uart_handle->_huart, (uint8_t *)receive_buffer + n, 1, wait_ms);

        if (HAL_TIMEOUT == state)
        {
            *preceive_length = (n + 1);
            return status_err;
        }
    }

    *preceive_length = n;
    return status_ok;
}

void uart_isr_callback(uart_ctrl_t *uart_handle)
{
    //uart_ctrl_t *uart_handle = UART_GET_CTRL(p);
    ASSERT(NULL != uart_handle);
    /* IDLE interrupt process */
    if (uart_handle->_huart->hdmarx)
    {
        /* DMA process */
        if ((__HAL_UART_GET_FLAG(uart_handle->_huart, UART_FLAG_IDLE) != RESET))
        {
            /* Clear interrupt flag */
            __HAL_UART_CLEAR_IDLEFLAG(uart_handle->_huart);

            /* Stop UART DMA Rx */
            // HAL_DMA_Abort(uart_handle->_huart->_hdma_rx); //别用这个，用这个就会出问题
            HAL_UART_DMAStop(uart_handle->_huart); // 天坑 HAL库dma和uart不能单独停止？？！

            if (uart_handle->_huart->gState == HAL_UART_STATE_BUSY_TX_RX)
            {
                uart_handle->_huart->gState = HAL_UART_STATE_BUSY_TX;
            }
            else
            {
                uart_handle->_huart->gState = HAL_UART_STATE_READY;
            }

            /* Receive & process the data */
            {
                uint32_t ulRecvd;
                // ulRecvd = UART_RXBUF_SIZE - uart_handle->_huart->_hdma_rx->Instance->CNDTR;
                ulRecvd = UART_RXBUF_SIZE - __HAL_DMA_GET_COUNTER(uart_handle->_huart->hdmarx);
                if (uart_handle->process_rx_function)
                {
                    TRACE("uart_handle->rx_buffer = %s\r\n", uart_handle->rx_buffer);
                    (uart_handle->process_rx_function)((uint8_t *)uart_handle->rx_buffer, (uint16_t)ulRecvd, uart_handle->isr_para);
                     memset(uart_handle->rx_buffer, 0, UART_RXBUF_SIZE);
                }
            }

            HAL_UART_Receive_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->rx_buffer), UART_RXBUF_SIZE);
            // HAL_UARTEx_ReceiveToIdle_DMA(uart_handle->_huart, (uint8_t *)(uart_handle->rx_buffer), UART_RXBUF_SIZE);
        }
    }
    else
    {
        /* Read DR register directly */
        if ((__HAL_UART_GET_FLAG(uart_handle->_huart, UART_FLAG_IDLE) != RESET))
        {
            if (uart_handle->_huart->gState == HAL_UART_STATE_BUSY_TX_RX)
            {
                uart_handle->_huart->gState = HAL_UART_STATE_BUSY_TX;
            }
            else
            {
                uart_handle->_huart->gState = HAL_UART_STATE_READY;
            }
            /* Receive & process the data */
//            {
//                uart_handle->rx_buffer[0] = uart_handle->_huart->Instance->DR;
//                if (uart_handle->process_rx_function)
//                {
//                    (uart_handle->process_rx_function)((uint8_t *)uart_handle->rx_buffer, 1, uart_handle->isr_para);
//                }
//            }
            {
                
                if (uart_handle->process_rx_function)
                {
                    (uart_handle->process_rx_function)((uint8_t *)uart_handle->rx_buffer, uart_handle->rx_length, uart_handle->isr_para);
                }
                uart_handle->rx_length = 0;
            }
            
            /* Clear interrupt flag */
            __HAL_UART_CLEAR_IDLEFLAG(uart_handle->_huart);
        }

        /* Read DR register directly */
        if ((__HAL_UART_GET_FLAG(uart_handle->_huart, UART_FLAG_RXNE) != RESET))
        {
            if (uart_handle->_huart->gState == HAL_UART_STATE_BUSY_TX_RX)
            {
                uart_handle->_huart->gState = HAL_UART_STATE_BUSY_TX;
            }
            else
            {
                uart_handle->_huart->gState = HAL_UART_STATE_READY;
            }
            
            /* Receive & process the data */
            {
                uart_handle->rx_buffer[uart_handle->rx_length] = uart_handle->_huart->Instance->DR;
                uart_handle->rx_length++;
            }
        }
        
    }
    return;
}

void uart_dma_rx_isr_callback(uart_ctrl_t *uart_handle)
{
    //uart_ctrl_t *uart_handle = UART_GET_CTRL(p);
    /* TODO: uart_dma_rx_isr_callback */
    ASSERT(NULL != uart_handle);
#if UART_TEST
    uart_handle->uart_dma_rx_isr_callback_count++;
#endif /* UART_TEST */
    return;
}

void uart_dma_tx_isr_callback(uart_ctrl_t *uart_handle)
{
    //uart_ctrl_t *uart_handle = UART_GET_CTRL(p);
    /* TODO: uart_dma_tx_isr_callback */
    ASSERT(NULL != uart_handle);
#if UART_TEST
    uart_handle->uart_dma_tx_isr_callback_count++;
#endif /* UART_TEST */
    return;
}

void uart_isr(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
#if UART_TEST
    uart_handle->uart_isr_count++;
#endif /* UART_TEST */
    (uart_handle->uart_isr_function)(uart_handle);
    // HAL_UART_IRQHandler(uart_handle->_huart);
    return;
}

void uart_dma_rx_isr(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
    
#if UART_TEST
    uart_handle->uart_dma_rx_isr_count++;
#endif /* UART_TEST */
    (uart_handle->dma_rx_isr_function)(uart_handle);
    // HAL_DMA_IRQHandler(uart_handle->_huart->_hdma_rx);
    return;
}

void uart_dma_tx_isr(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
#if UART_TEST
    uart_handle->uart_dma_tx_isr_count++;
#endif /* UART_TEST */
    (uart_handle->dma_tx_isr_function)(uart_handle);
    // HAL_DMA_IRQHandler(uart_handle->_huart->_hdma_tx);
    return;
}

#if UART_DEBUG
status_t uart_show_status(uart_ctrl_t *uart_handle)
{
    // uart_ctrl_t *uart_handle = UART_GET_CTRL(uart_handle);

    ASSERT(NULL != uart_handle);
    TRACE("Uart handle: %08X\n", uart_handle);
    TRACE("    _huart               : %08X\r\n", uart_handle->_huart);
    TRACE("    _hdma_rx              : %08X\r\n", uart_handle->_hdma_rx);
    TRACE("    _hdma_tx              : %08X\r\n", uart_handle->_hdma_tx);

    TRACE("    uart_isr_function       : %08X\r\n", uart_handle->uart_isr_function);
    TRACE("    dma_rx_isr_function      : %08X\r\n", uart_handle->dma_rx_isr_function);
    TRACE("    dma_tx_isr_function      : %08X\r\n", uart_handle->dma_tx_isr_function);
    TRACE("    process_rx_function        : %08X\r\n", uart_handle->process_rx_function);

    TRACE("    uart_irq            : %d\r\n", uart_handle->uart_irq);
    TRACE("    dma_rx_irq           : %d\r\n", uart_handle->dma_rx_irq);
    TRACE("    dma_tx_irq           : %d\r\n", uart_handle->dma_tx_irq);
    TRACE("    isr_para           : %08X\r\n", uart_handle->isr_para);

#if UART_TEST
    TRACE("    uart_isr_count        : %d\n", uart_handle->uart_isr_count);
    TRACE("    uart_dma_rx_isr_count   : %d\n", uart_handle->uart_dma_rx_isr_count);
    TRACE("    uart_dma_tx_isr_count   : %d\n", uart_handle->uart_dma_tx_isr_count);
    TRACE("    uart_dma_rx_isr_callback_count : %d\n", uart_handle->uart_dma_rx_isr_callback_count);
    TRACE("    uart_dma_tx_isr_callback_count : %d\n", uart_handle->uart_dma_tx_isr_callback_count);
    TRACE("    \n");
#endif /* UART_TEST */

    return status_ok;
}
#endif /* UART_DEBUG */

#endif /* UART_ENABLE */
