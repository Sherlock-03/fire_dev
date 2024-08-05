/*
    Cli.c

    Implementation File for Cli Module

    Reference: FreeRTOS Sample-CLI-commands.c
*/

/* Copyright 2019 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 11Dec18, Karl Created
    01b, 01Aug19, Karl Reconstructured Cli lib
    01c, 27Aug19, Karl Modified include files
*/

/* Includes. */
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "lib/cli/lib_cli.h"
#include "lib/debug/lib_debug.h"

#if CLI_ENABLE

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
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* CLI_ASSERT */

/* Functions */
status_t cli_init(void)
{
    /* Do nothing */
    return status_ok;
}

status_t cli_terminal(void)
{
    /* Do nothing */
    return status_ok;
}

status_t cli_load_cmd(void *pvCmd)
{
#if (CLI_ENABLE_UART || CLI_ENABLE_UDP)
    FreeRTOS_CLIRegisterCommand(pvCmd);
#endif /* (CLI_ENABLE_UART || CLI_ENABLE_UDP) */
    return status_ok;
}

#endif /* CLI_ENABLE */
