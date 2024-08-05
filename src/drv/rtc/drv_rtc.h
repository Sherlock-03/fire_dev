/*
    Rtc.h

    Head File for Rtc Module
*/

/* Copyright 2019 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 15Jul19, Karl Created
    01b, 26Aug19, Karl Modified include files
*/

#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus */

/* Includes */
#include <stdint.h>
#include "lib/type/lib_type.h"
#include "drv/rtc/drv_rtc_config.h"
#include "drv/rtc/drv_rtc_ds1338.h"

    /* Types */
    typedef enum
    {
        RTC_TYPE_STM32,
        RTC_TYPE_DS1302,
        RTC_TYPE_DS1338,
        RTC_TYPE_SIZE
    } RtcType_t;

    /* Functions */
    status_t RtcInit(void);
    status_t RtcTerm(void);
    status_t RtcConfig(RtcType_t xRtcType, const void *pvConfig, uint16_t usConfigSize);

    Time_t RtcReadTime(RtcType_t xRtcType);
    status_t RtcWriteTime(RtcType_t xRtcType, Time_t xTm);

#if RTC_TEST
    status_t RtcTest(uint8_t ucSel);
#endif /* RTC_TEST */

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* __RTC_H__ */
