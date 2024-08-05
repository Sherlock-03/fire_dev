/*
    RbufConfig.h

    Configuration File for Rbuf Module
*/

/* Copyright 2019 Shanghai BiNY Inc. */

/*
    modification history
    --------------------
    01a, 12Jul18, Karl Created
*/

#ifndef _RBUF_CONFIG_H
#define _RBUF_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */

/* Includes */
#include "app/arm_application/config.h"

/* Configuration defines */
#ifndef RBUF_ENABLE
#define RBUF_ENABLE (0)
#endif
#ifndef RBUF_RTOS
#define RBUF_RTOS (1)
#endif
#ifndef RBUF_DEBUG
#define RBUF_DEBUG (0)
#endif
#ifndef RBUF_ASSERT
#define RBUF_ASSERT (0)
#endif
#ifndef RBUF_TEST
#define RBUF_TEST (0)
#endif
#ifndef RBUF_MSGQ_SIZE
#define RBUF_MSGQ_SIZE (10)
#endif
#ifndef RBUF_MSGQ_WAITMS
#define RBUF_MSGQ_WAITMS (500)
#endif

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* __RBUF_CONFIG_H__ */
