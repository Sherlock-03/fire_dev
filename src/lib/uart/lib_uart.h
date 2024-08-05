/*
    Uart.h

    Head File for Uart Module
*/

/* Copyright 2018 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 20Sep18, Karl Created
    01b, 24Dec18, Karl Modified, Added UartStartIt & UartStopIt
    01c, 14Jul19, Karl Reconstructured Uart lib
    01d, 28Aug19, Karl Added UartIsrCb support for Uart isr without DMA
    01e, 03Dec19, Karl Added UartConfigComEx
*/

#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include <stdint.h>
#include <stm32f1xx_hal.h>
#include "lib/type/lib_type.h"
#include "lib/uart/lib_uart_config.h"

    /* Types */
    // typedef uint32_t uart_ctrl_t;
    
    typedef struct uart_ctrl_t uart_ctrl_t;

    typedef void (*uart_isr_function_t)(uart_ctrl_t *);
    typedef status_t (*uart_process_function_t)(uint8_t *, uint16_t, void *);

    struct uart_ctrl_t
    {
        UART_HandleTypeDef *_huart;
        DMA_HandleTypeDef *_hdma_rx;
        DMA_HandleTypeDef *_hdma_tx;

        uint8_t tx_buffer[UART_TXBUF_SIZE];
        uint8_t rx_buffer[UART_RXBUF_SIZE];
        uint16_t rx_length;

        uart_isr_function_t uart_isr_function;
        uart_isr_function_t dma_rx_isr_function;
        uart_isr_function_t dma_tx_isr_function;
        uart_process_function_t process_rx_function;

        IRQn_Type uart_irq;
        IRQn_Type dma_rx_irq;
        IRQn_Type dma_tx_irq;
        void *isr_para;
        
        

        #if UART_TEST
        uint32_t uart_isr_count;
        uint32_t uart_dma_rx_isr_count;
        uint32_t uart_dma_tx_isr_count;
        uint32_t uart_dma_rx_isr_callback_count;
        uint32_t uart_dma_tx_isr_callback_count;
        #endif /* UART_TEST */
    };

    typedef struct
    {
        uint32_t ulWordLength;
        uint32_t ulStopBits;
        uint32_t ulParity;
        uint32_t ulHwFlowCtl;
    } UartPortPara_t;

    /* Functions */
    status_t uart_config_callback(uart_ctrl_t *uart_handle, uart_process_function_t process_rx_function, uart_isr_function_t uart_isr_function, uart_isr_function_t dma_rx_isr_function, uart_isr_function_t dma_tx_isr_function, void *isr_para);
    status_t uart_config_handle(uart_ctrl_t *uart_handle, UART_HandleTypeDef *_huart, DMA_HandleTypeDef *_hdma_rx, DMA_HandleTypeDef *_hdma_tx);

    status_t uart_start_it(uart_ctrl_t *uart_handle);
    status_t uart_stop_it(uart_ctrl_t *uart_handle);
    status_t uart_dma_send(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t receive_length, uint16_t wait_ms);

    status_t uart_block_send(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t receive_length, uint16_t wait_ms);
    status_t uart_block_read(uart_ctrl_t *uart_handle, uint8_t *receive_buffer, uint16_t *preceive_length, uint16_t wait_ms);
    void uart_isr_callback(uart_ctrl_t *uart_handle);
    void uart_dma_rx_isr_callback(uart_ctrl_t *uart_handle);
    void uart_dma_tx_isr_callback(uart_ctrl_t *uart_handle);
    void uart_isr(uart_ctrl_t *uart_handle);
    void uart_dma_rx_isr(uart_ctrl_t *uart_handle);
    void uart_dma_tx_isr(uart_ctrl_t *uart_handle);

#if UART_TEST
  status_t UartTest(void);
#endif /* UART_TEST */

#if UART_DEBUG
  status_t UartShowStatus(uart_ctrl_t xHandle);
#endif /* UART_DEBUG */

#if UART_ENABLE_MSP
  void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle);
  void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle);
#endif /* UART_ENABLE_MSP */

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* __UART_H */

#if 0

  /* new types */
  typedef uint32_t uart_ctrl_t;
  typedef void (*uart_isr_function_t)(void *);
  typedef status_t (*uart_process_rx_function_t)(uint8_t *, uint16_t, void *);

  status_t uart_init(void);
  uart_ctrl_t uart_create(void);
  status_t uart_config_handle(uart_ctrl_t uart_handle, UART_HandleTypeDef *huart);
  status_t uart_config_callback(uart_ctrl_t uart_handle, uart_isr_function_t uart_isr_function, uart_isr_function_t dma_tx_isr_function, uart_isr_function_t dma_rx_isr_function,  uart_process_rx_function_t process_rx_function);
  status_t uart_dma_send(uart_ctrl_t uart_handle, uint8_t *dma_send_buffer, uint16_t buffer_length, uint16_t wait_ms);
  status_t uart_block_send(uart_ctrl_t uart_handle, uint8_t *dma_send_buffer, uint16_t buffer_length, uint16_t wait_ms);

  void uart_isr_callback(void *p);
  void uart_isr(uart_ctrl_t uart_handle);
  void uart_dma_rx_isr_callback(void *p);
  void uart_dma_tx_isr_callback(void *p);
    

  void uart_dma_rx_isr(uart_ctrl_t uart_handle);
  void uart_dma_tx_isr(uart_ctrl_t uart_handle);

#if UART_ENABLE
  /* Types */
  typedef uint32_t uart_ctrl_t;

  typedef struct
  {
    uint32_t ulWordLength;
    uint32_t ulStopBits;
    uint32_t ulParity;
    uint32_t ulHwFlowCtl;
  } UartPortPara_t;

  typedef void (*uart_isr_function_t)(void *);
  typedef status_t (*uart_process_function_t)(uint8_t *, uint16_t, void *);

  /* Functions */
  status_t UartInit(void);
  status_t UartTerm(void);

  uart_ctrl_t UartCreate(void);
  status_t UartDelete(uart_ctrl_t xHandle);

  status_t UartConfigCb(uart_ctrl_t xHandle, uart_process_function_t CbRxProc, uart_isr_function_t CbUartIsr, uart_isr_function_t CbDmaRxIsr, uart_isr_function_t CbDmaTxIsr, void *pIsrPara);
  status_t UartConfigCom(uart_ctrl_t xHandle, USART_TypeDef *pxInstance, uint32_t ulBaudRate, IRQn_Type xIrq);
  status_t UartConfigComEx(uart_ctrl_t xHandle, USART_TypeDef *pxInstance, uint32_t ulBaudRate, IRQn_Type xIrq, UartPortPara_t xPara);
  status_t UartConfigRxDma(uart_ctrl_t xHandle, DMA_Channel_TypeDef *pDmaChan, IRQn_Type Irq);
  status_t UartConfigTxDma(uart_ctrl_t xHandle, DMA_Channel_TypeDef *pDmaChan, IRQn_Type Irq);

  status_t UartStartIt(uart_ctrl_t xHandle);
  status_t UartStopIt(uart_ctrl_t xHandle);

  /* XXX: UartDmaSend should not be called in isr! */
  status_t UartDmaSend(uart_ctrl_t xHandle, uint8_t *pucBuf, uint16_t usLength, uint16_t usWaitMs);
  status_t UartBlkSend(uart_ctrl_t xHandle, uint8_t *pucBuf, uint16_t usLength, uint16_t usWaitMs);
  status_t UartBlkRead(uart_ctrl_t xHandle, uint8_t *pucBuf, uint16_t *pusLength, uint16_t usWaitMs);

  void UartIsrCb(void *p);
  void UartDmaRxIsrCb(void *p);
  void UartDmaTxIsrCb(void *p);
  void UartIsr(uart_ctrl_t xHandle);
  void UartDmaRxIsr(uart_ctrl_t xHandle);
  void UartDmaTxIsr(uart_ctrl_t xHandle);

#if UART_TEST
  status_t UartTest(void);
#endif /* UART_TEST */

#if UART_DEBUG
  status_t UartShowStatus(uart_ctrl_t xHandle);
#endif /* UART_DEBUG */

#if UART_ENABLE_MSP
  void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle);
  void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle);
#endif /* UART_ENABLE_MSP */

#endif /* UART_ENABLE */

#endif
