/*
    Rtc.c

    Implementation File for Rtc Module
*/

/* Copyright 2019 Shanghai Master Inc. */

/*
    modification history
    --------------------
    01a, 15Jul19, Karl Created
    01b, 26Aug19, Karl Modified include files
*/

/* Includes */
#include <string.h>
#include "drv/rtc/drv_rtc.h"
#include <time.h>

#if RTC_ENABLE

/* Debug config */
#if RTC_DEBUG
#undef TRACE
#define TRACE(...) DebugPrintf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* RTC_DEBUG */
#if RTC_ASSERT
#undef ASSERT
#define ASSERT(a)                                                  \
    while (!(a))                                                   \
    {                                                              \
        DebugPrintf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* RTC_ASSERT */

/* Functions */
status_t RtcInit(void)
{
    status_t ret;
#if RTC_DS1302_ENABLE
    ret = RtcDs1302Init();
    if (status_ok != ret)
    {
        return ret;
    }
#endif
#if RTC_STM32_ENABLE
    ret = RtcStm32Init();
    if (status_ok != ret)
    {
        return ret;
    }
#endif
#if RTC_DS1338_ENABLE
    ret = RtcDs1338Init();
    if (status_ok != ret)
    {
        return ret;
    }
#endif
    return ret;
}

status_t RtcTerm(void)
{
    status_t ret;
#if RTC_DS1302_ENABLE
    ret = RtcDs1302Term();
    if (status_ok != ret)
    {
        return ret;
    }
#endif
#if RTC_STM32_ENABLE
    ret = RtcStm32Term();
    if (status_ok != ret)
    {
        return ret;
    }
#endif
#if RTC_DS1338_ENABLE
    ret = status_ok;
#endif
    return ret;
}

status_t RtcConfig(RtcType_t xRtcType, const void *pvConfig, uint16_t usConfigSize)
{
    status_t ret;
    switch (xRtcType)
    {
#if RTC_STM32_ENABLE
    case RTC_TYPE_STM32:
        ASSERT(sizeof(RtcStm32Config_t) == usConfigSize);
        ret = RtcStm32Config((RtcStm32Config_t *)pvConfig);
        break;
#endif
#if RTC_DS1302_ENABLE
    case RTC_TYPE_DS1302:
        ASSERT(sizeof(Ds1302Config_t) == usConfigSize);
        ret = RtcDs1302Config((Ds1302Config_t *)pvConfig);
        break;
#endif
#if RTC_DS1338_ENABLE
    case RTC_TYPE_DS1338:
        ret = status_ok;
        break;
#endif

    default:
        ASSERT(0);
        break;
    }
    return ret;
}

Time_t RtcReadTime(RtcType_t xRtcType)
{
    Time_t xTm;
    switch (xRtcType)
    {
#if RTC_STM32_ENABLE
    case RTC_TYPE_STM32:
        xTm = RtcStm32ReadTime();
        break;
#endif
#if RTC_DS1302_ENABLE
    case RTC_TYPE_DS1302:
        xTm = RtcDs1302ReadTimeBurst();
        break;
#endif
#if RTC_DS1338_ENABLE
    case RTC_TYPE_DS1338:
        xTm = RtcDs1338ReadTime();

        break;
#endif
    default:
        /* We should never get here! */
        ASSERT(0);
        break;
    }
    return xTm;
}

status_t RtcWriteTime(RtcType_t xRtcType, Time_t xTm)
{
    status_t ret;
    switch (xRtcType)
    {
#if RTC_STM32_ENABLE
    case RTC_TYPE_STM32:
        ret = RtcStm32WriteTime(xTm);
        break;
#endif
#if RTC_DS1302_ENABLE
    case RTC_TYPE_DS1302:
        ret = RtcDs1302WriteTimeBurst(xTm);
        break;
#endif
#if RTC_DS1338_ENABLE
    case RTC_TYPE_DS1338:
        ret = RtcDs1338WriteTime(xTm);
        break;
#endif
    default:
        /* We should never get here! */
        ASSERT(0);
        break;
    }
    return ret;
}

#endif /* RTC_ENABLE */
