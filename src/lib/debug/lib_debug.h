/*
    Debug.h

    Head File for Debug Module
*/

/* Copyright 2019 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 12Sep18, Karl Created
    01b, 15Nov18, Karl Modified
    01c, 15Jul19, Karl Reconstructured Debug module
    01d, 26Aug19, Karl Modified include files
*/

#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include <stdint.h>
#include "lib/type/lib_type.h"
#include "lib/debug/lib_debug_config.h"
#include "lib/debug/lib_debug_uart.h"

    /* Types */
    typedef enum
    {
        DEBUG_CHAN_NULL = 0,
        DEBUG_CHAN_UART = 0x01,
        DEBUG_CHAN_TCP = 0x02,
        DEBUG_CHAN_UDP = 0x04,
    } DebugChan_t;

    /* Functions */
    status_t debug_init(void);
    status_t debug_term(void);
    status_t debug_channel_set(DebugChan_t xDebugChan);
    status_t debug_printf(char *cFormat, ...);

#if DEBUG_TEST
    status_t DebugTest(void);
#endif /* DEBUG_TEST */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DEBUG_H */
