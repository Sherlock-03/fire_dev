/*
    rtc_time.h

    Head File for Time Module
*/

/* Copyright 2023 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 17Nov23, Karl Created
*/

#ifndef ___TIME_H
#define ___TIME_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "lib/type/lib_type.h"

/* Functions */
status_t DrvTimeInit(void);
status_t DrvTimeTerm(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ___TIME_H__ */
