/*
    rtc_ime.c

    Implementation File for Time Module
*/

/*
    modification history
    --------------------
    01a, 17Nov23, Karl Created
*/

/* Includes */
#include "app/arm_application/include.h"

/* Debug config */
#if TIME_DEBUG
    #undef TRACE
    #define TRACE(...)  DebugPrintf(__VA_ARGS__)
#else
    #undef TRACE
    #define TRACE(...)
#endif /* TIME_DEBUG */
#if TIME_ASSERT
    #undef ASSERT
    #define ASSERT(a)   while(!(a)){DebugPrintf("ASSERT failed: %s %d\n", __FILE__, __LINE__);}
#else
    #undef ASSERT
    #define ASSERT(...)
#endif /* TIME_ASSERT */

/* Local defines */
#if RTC_RTOS || 1
static osMutexId s_xRtcMutex;

#define MEM_MUTEX_INIT()                                \
    do                                                  \
    {                                                   \
        s_xRtcMutex = osMutexNew(NULL);                 \
        if (s_xRtcMutex == NULL)                        \
        {                                               \
            /* Handle error */                          \
        }                                               \
    } while (0)
#define RTC_LOCK()   osMutexAcquire(s_xRtcMutex, osWaitForever)
#define RTC_UNLOCK() osMutexRelease(s_xRtcMutex)
#else
#define RTC_MUTEX_INIT()
#define RTC_LOCK()
#define RTC_UNLOCK()
#endif /* RTC_RTOS */ 

/* Functions */
status_t DrvTimeInit(void)
{
#if RTC_DS1302_ENABLE
    Ds1302Config_t xConfig;
    
    xConfig.xRst.pxPort = PORT(DS1302_RST);
    xConfig.xRst.usPin  = PIN(DS1302_RST);
    xConfig.xClk.pxPort = PORT(DS1302_CLK);
    xConfig.xClk.usPin  = PIN(DS1302_CLK);
    xConfig.xIo.pxPort  = PORT(DS1302_IO);
    xConfig.xIo.usPin   = PIN(DS1302_IO);
    
    RtcDs1302Init();
    RtcDs1302Config(&xConfig);
#endif
#if RTC_DS1338_ENABLE
    RtcDs1338Init();
    
#endif 
    
    return status_ok;
}

status_t DrvTimeTerm(void)
{
    /* Do nothing */
    return status_ok;
}

static void prvCliCmdRtcGet(cli_printf cliprintf, int argc, char** argv)
{
    CHECK_CLI();
    RTC_LOCK();
    Time_t xTm = RtcReadTime(RTC_TYPE_DS1338);
    //cliprintf("RTC time: %d, %s\r\n", mktime(&xTm), asctime(&xTm)); 
    cliprintf("RTC time: %d, ", mktime(&xTm)); 
    cliprintf("%s\r\n", asctime(&xTm));
    RTC_UNLOCK();
}
CLI_CMD_EXPORT(rtc_get, show rtc time, prvCliCmdRtcGet)

static void prvCliCmdRtcSet(cli_printf cliprintf, int argc, char** argv)
{
    CHECK_CLI();
    RTC_LOCK();
    if (argc != 7) {
        cliprintf("rtc_set YYYY MM DD hh mm ss\n");
        return;
    }
    int lYear   = atoi(argv[1]);    /* YYYY */
    int lMon    = atoi(argv[2]);
    int lDay    = atoi(argv[3]);
    int lHour   = atoi(argv[4]);
    int lMin    = atoi(argv[5]);
    int lSec    = atoi(argv[6]);
    
    Time_t xTm;
    xTm.tm_year = lYear - 1900;
    xTm.tm_mon  = lMon - 1;
    xTm.tm_mday = lDay;
    xTm.tm_hour = lHour;
    xTm.tm_min  = lMin;
    xTm.tm_sec  = lSec;
    RtcWriteTime(RTC_TYPE_DS1338, xTm);
    
    //cliprintf("RTC time: %d, %s\r", mktime(&xTm), asctime(&xTm)); 
    cliprintf("RTC time: %d, ", mktime(&xTm)); 
    cliprintf("%s\r\n", asctime(&xTm));
    RTC_UNLOCK();
}
CLI_CMD_EXPORT(rtc_set, set rtc time, prvCliCmdRtcSet)
