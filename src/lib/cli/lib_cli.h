/*
    Cli.h

    Head File for Cli Module

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

#ifndef __LIB_CLI_H
#define __LIB_CLI_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include <stdint.h>
#include "lib/type/lib_type.h"
#include "lib/cli/lib_cli_config.h"
#include "lib/cli/lib_cli_custom.h"

/* Defines */
#define CLI_CMD_EXPORT(name, help, func)                         \
    const char __cli_##name##_name[] = #name;                    \
    const char __cli_##name##_help[] = #help;                    \
    USED const cli_command_t __cli_##name SECTION("CliCmdTab") = \
        {                                                        \
            __cli_##name##_name,                                 \
            __cli_##name##_help,                                 \
            func};

    /* Functions */
    status_t cli_init(void);
    status_t cli_terminal(void);
    status_t cli_load_cmd(void *pvCmd);

#if CLI_TEST
    status_t CliTestFreeRtos(uint8_t ucSel);
    status_t CliTestCustom(uint8_t ucSel);
#endif /* CLI_TEST */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LIB_CLI_H */
