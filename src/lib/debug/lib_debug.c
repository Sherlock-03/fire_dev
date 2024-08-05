#include <stdio.h>
#include <stdarg.h>
#include <cmsis_os2.h>
#include "FreeRTOS.h"
#include "task.h"
#include "lib/debug/lib_debug.h"

#if DEBUG_ENABLE

/* Pragmas */
#pragma diag_suppress 550 /* warning: #550-D: variable was set but never used */

/* Debug config */
#if DEBUG_DEBUG
#undef TRACE
#define TRACE(...)
#else
#undef TRACE
#define TRACE(...)
#endif /* DEBUG_DEBUG */
#if DEBUG_ASSERT
#undef ASSERT
#define ASSERT(a) \
    while (!(a))  \
        ;
#else
#undef ASSERT
#define ASSERT(...)
#endif /* DEBUG_ASSERT */

/* Local variables */
static DebugChan_t s_xDebugChan = DEBUG_CHAN_NULL;
static osMutexId_t s_xDebugMutex = NULL;
static Bool_t s_bInit = FALSE;

/* Forward declaration */
static int prvIsInIsr(void);
static void prvDebugLock(void);
static void prvDebugUnlock(void);

/* Functions */
status_t debug_init(void)
{
    s_xDebugMutex = osMutexNew(NULL);
    s_bInit = TRUE;
    return status_ok;
}

status_t debug_term(void)
{
    return status_ok;
}

status_t debug_channel_set(DebugChan_t xDebugChan)
{
    s_xDebugChan = xDebugChan;
    return status_ok;
}

DebugChan_t debug_channel_get(void)
{
    return s_xDebugChan;
}

status_t debug_printf(char *cFormat, ...)
{
    uint16_t usLength = 0;
    status_t xRet = status_ok;
    static char cBuf[DEBUG_BUF_SIZE];

    ASSERT(s_bInit);
    /* "TCP & UDP" does not support printf function in isr */
    if (((DEBUG_CHAN_TCP == s_xDebugChan) || (DEBUG_CHAN_UDP == s_xDebugChan)) && prvIsInIsr())
    {
        return status_err;
    }

    /* Enter critical section */
    prvDebugLock();

    va_list va;
    va_start(va, cFormat);
    usLength = vsprintf(cBuf, cFormat, va);
    switch (s_xDebugChan)
    {
#if DEBUG_ENABLE_UART
    case DEBUG_CHAN_UART:
        xRet = DebugUartPrintfDirect(cBuf, usLength);
        break;
#endif /* DEBUG_ENABLE_UART */
#if DEBUG_ENABLE_TCP
    case DEBUG_CHAN_TCP:
        xRet = DebugTcpPrintfDirect(cBuf, usLength);
        break;
#endif /* DEBUG_ENABLE_TCP */
#if DEBUG_ENABLE_UDP
    case DEBUG_CHAN_UDP:
        xRet = DebugUdpPrintfDirect(cBuf, usLength);
        break;
#endif /* DEBUG_ENABLE_UDP */
    default:
        /* Do nothing! */
        break;
    }
    va_end(va);

    /* Leave critical section */
    prvDebugUnlock();

    return xRet;
}

static int prvIsInIsr(void)
{
    return osKernelGetState() == osKernelRunning;
}

static void prvDebugLock(void)
{
    ASSERT(s_bInit);
    if (prvIsInIsr())
    {
        taskDISABLE_INTERRUPTS();
    }
    else
    {
        ASSERT(NULL != s_xDebugMutex);
        osMutexAcquire(s_xDebugMutex, osWaitForever);
    }
    return;
}

static void prvDebugUnlock(void)
{
    ASSERT(s_bInit);
    if (prvIsInIsr())
    {
        taskENABLE_INTERRUPTS();
    }
    else
    {
        ASSERT(NULL != s_xDebugMutex);
        osMutexRelease(s_xDebugMutex);
    }
    return;
}

#endif /* DEBUG_ENABLE */
