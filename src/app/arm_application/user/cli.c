/*
    Cli.c

    Implementation File for App Cli Module
*/

/* Copyright 2023 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 17Nov23, Karl Created
    01b, 24Nov23, Karl Added reset and upgrade
*/

/* Includes */
#include "app/arm_application/Include.h"

/* Debug config */
#if CLI_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* CLI_DEBUG */
#if CLI_ASSERT
#undef ASSERT
#define ASSERT(a)                                                  \
    while (!(a))                                                   \
    {                                                              \
        DebugPrintf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* CLI_ASSERT */

/* Local types */

/* Forward declaration */
static void prvCliUartTask(void *pvPara);
static void prvCliUartPrintf(const char *cFormat, ...);
status_t prvCliUartRecvCb(uint8_t *pucBuf, uint16_t usLength, void *pvIsrPara);

/* Local variables */
#if CLI_ENABLE_SECURITY
static Bool_t s_bEnCli = FALSE;
#else
static Bool_t s_bEnCli = TRUE;
#endif /* CLI_ENABLE_SECURITY */
static const char *s_cConfigMark = "admin";
cli_uart_ctrl_t cli_uart_ctrl;

/* Functions */
status_t app_cli_init(void)
{
    extern const int CliCmdTab$$Base;
    extern const int CliCmdTab$$Limit;

    cli_init();
    cli_custom_init();
    cli_custom_load_cmd((const cli_command_t *)(&CliCmdTab$$Base), ((uint32_t)&CliCmdTab$$Limit - (uint32_t)&CliCmdTab$$Base) / sizeof(cli_command_t));

    xTaskCreate(prvCliUartTask, "tCli", 256, (void *)&cli_uart_ctrl, tskIDLE_PRIORITY, NULL);

    return status_ok;
}

status_t AppCliTerm(void)
{
    /* Do nothing */
    return status_ok;
}

Bool_t CliIsEnabled(void)
{
    return s_bEnCli;
}

static void prvCliUartTask(void *pvPara)
{
    cli_uart_ctrl_t *pxCtrl = (cli_uart_ctrl_t *)pvPara;

    TRACE("Enter prvCliUartTask\r\n");

    /* Create the queues used to hold Rx characters. */
    pxCtrl->xRxQueue = xQueueCreate(256, (portBASE_TYPE)sizeof(char));

#if 0
    /* Create UART com port */
    pxCtrl->xUart = UartCreate();
    UartConfigCb(pxCtrl->xUart, prvCliUartRecvCb, UartIsrCb, UartDmaRxIsrCb, UartDmaTxIsrCb, pxCtrl);
#if CLI_ENABLE_UART_DMA
    UartConfigRxDma(pxCtrl->xUart, CLI_UART_DMA_RX_CHAN, CLI_UART_DMA_RX_ISR);
    UartConfigTxDma(pxCtrl->xUart, CLI_UART_DMA_TX_CHAN, CLI_UART_DMA_TX_ISR);
#endif /* CLI_ENABLE_UART_DMA */
    UartConfigCom(pxCtrl->xUart, CLI_UART_HANDLE, CLI_UART_BAUDRATE, CLI_UART_ISR);
    pxCtrl->bInit = TRUE;
#endif
    
#if 1
    // pxCtrl->xUart = uart_create();
    //TRACE("cli init run\r\n");
    uart_config_callback(&pxCtrl->xUart, prvCliUartRecvCb, uart_isr_callback, uart_dma_rx_isr_callback, uart_dma_tx_isr_callback, pxCtrl);
    //TRACE("cli init setp 1 run\r\n");
    uart_config_handle(&pxCtrl->xUart, &huart1, &hdma_usart1_rx, &hdma_usart1_tx);
    pxCtrl->bInit = TRUE;

#endif

    //TRACE("cli init run ok\r\n");
    /* Read and process data */
    while (1)
    {
        char cChr;
        if (xQueueReceive(pxCtrl->xRxQueue, &cChr, portMAX_DELAY) == pdPASS)
        {
            // TRACE("Received character from queue: %c\n", cChr);
            cli_custom_input(prvCliUartPrintf, cChr);
        }
    }
}

static void prvCliUartPrintf(const char *cFormat, ...)
{
    cli_uart_ctrl_t *pxCtrl = &cli_uart_ctrl;

    if (NULL != pxCtrl)
    {
        va_list va;
        va_start(va, cFormat);
        uint16_t usLength = vsprintf(pxCtrl->cFmtBuffer, cFormat, va);
        if (usLength)
        {
            uart_block_send(&pxCtrl->xUart, (uint8_t *)pxCtrl->cFmtBuffer, usLength, 1000);
        }
    }
    return;
}

status_t prvCliUartRecvCb(uint8_t *pucBuf, uint16_t usLength, void *pvIsrPara)
{

    cli_uart_ctrl_t *pxCtrl = (cli_uart_ctrl_t *)pvIsrPara;

    // uart_block_send(pxCtrl->xUart, pucBuf, usLength, 10);

    TRACE("cli cb run\r\n");
    ASSERT(NULL != pxCtrl);

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    for (uint16_t n = 0; n < usLength; n++)
    {
        xQueueSendFromISR(pxCtrl->xRxQueue, pucBuf + n, &xHigherPriorityTaskWoken);
    }

    if (xHigherPriorityTaskWoken)
    {
        TRACE("clid xHigherPriorityTaskWoken");
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    return status_ok;
}

#if 0
void CLI_UART_ISR_HANDLER(void)
{
    UartIsr(cli_uart_ctrl.xUart);
}
#if CLI_ENABLE_UART_DMA
#ifdef CLI_UART_DMA_RX_ISR_HANDLER
void CLI_UART_DMA_RX_ISR_HANDLER(void)
{
    UartDmaRxIsr(cli_uart_ctrl.xUart);
}
#endif /* CLI_UART_DMA_RX_ISR_HANDLER */

#ifdef CLI_UART_DMA_TX_ISR_HANDLER
void CLI_UART_DMA_TX_ISR_HANDLER(void)
{
    UartDmaTxIsr(cli_uart_ctrl.xUart);
}
#endif /* CLI_UART_DMA_TX_ISR_HANDLER */
#endif /* CLI_ENABLE_UART_DMA */
#endif

static void prvCliCmdEncli(cli_printf cliprintf, int argc, char **argv)
{
    if (3 == argc)
    {
        int lEnCli;
#if CLI_ENABLE_SECURITY
        if (0 != strcmp(argv[1], s_cConfigMark))
        {
            cliprintf("CLI error: wrong config mark\n");
            return;
        }
#endif /* CLI_ENABLE_SECURITY */
        lEnCli = atoi(argv[2]);
        if (lEnCli > 0)
        {
            s_bEnCli = TRUE;
            cliprintf("Enable cli ok\n");
        }
        else
        {
            s_bEnCli = FALSE;
            cliprintf("Disable cli ok\r\n");
        }
    }
    else
    {
        cliprintf("CLI error: wrong parameters\r\n");
    }
    return;
}
CLI_CMD_EXPORT(encli, enable cli, prvCliCmdEncli)

static void prvCliCmdReset(cli_printf cliprintf, int argc, char **argv)
{
    CHECK_CLI();

    NVIC_SystemReset();
}
CLI_CMD_EXPORT(reset, system reset, prvCliCmdReset)





#if 0
static void prvCliCmdUpgrade(cli_printf cliprintf, int argc, char **argv)
{
    CHECK_CLI();

    uint32_t ulUpdateMark = 0x1234ABCD;
    MemFlashWrite(0, sizeof(ulUpdateMark), (uint8_t *)&ulUpdateMark);

    cliprintf("enter upgrade mode after system reset\n");
}
CLI_CMD_EXPORT(upgrade, enter upgrade mode after system reset, prvCliCmdUpgrade)
#endif
