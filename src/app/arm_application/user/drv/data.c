/*
    data.c

    Implementation File for App data Module
*/

/*
    modification history
    --------------------
    01a, 30May24, Jasper Created

*/

/* Includes */
#include "app/arm_application/include.h"

/* Debug config */
#if DATA_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* DATA_DEBUG */
#if DATA_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* DATA_ASSERT */

/* Forward declaration */
static Bool_t prvChkCrc(uint8_t *pucData, uint16_t usLength);
static uint8_t prvCalcCrc(uint8_t *pucData, uint16_t usLength);

/* Global variables */
Data_t g_xData;
uint16_t g_usMaxCurAd;

/* Functions */
status_t AppDataInit(void)
{
    TRACE("AppDataInit\r\n");
    DataLoad(&g_xData);
    return status_ok;
}

status_t AppDataTerm(void)
{
    /* Do nothing */
    return status_ok;
}

status_t DataLoad(OUT Data_t *pxData)
{
    Data_t xData;

    /* Read from page1 */
    MemFlashRead(FLASH_SAVE_PAGE1, sizeof(Data_t), (uint8_t *)&xData);
    TRACE("DataLoad = %d\r\n", (xData.head));
    if ((FLASH_DATA_HEAD == xData.head) && (prvChkCrc((uint8_t *)&xData, sizeof(xData))))
    {
        if (pxData)
        {
            *pxData = xData;
        }
        return status_ok;
    }
    TRACE("data load ok1\r\n");

    /* Read from page2 */
    MemFlashRead(FLASH_SAVE_PAGE2, sizeof(Data_t), (uint8_t *)&xData);
    if ((FLASH_DATA_HEAD == xData.head) && (prvChkCrc((uint8_t *)&xData, sizeof(xData))))
    {
        if (pxData)
        {
            *pxData = xData;
        }
        return status_ok;
    }
    TRACE("FLASH_SAVE_PAGE2\r\n");

    /* Init FLASH data */
    Data_t xDataInit = APP_DATA_INIT;
    xDataInit.crc = prvCalcCrc((uint8_t *)&xDataInit, sizeof(Data_t) - 1);
    TRACE("APP_DATA_INIT ok\r\n");
    MemFlashWrite(FLASH_SAVE_PAGE1, sizeof(Data_t), (uint8_t *)&xDataInit);
    TRACE("MemFlashWrite FLASH_SAVE_PAGE1\r\n");
    MemFlashWrite(FLASH_SAVE_PAGE2, sizeof(Data_t), (uint8_t *)&xDataInit);
    if (pxData)
    {
        *pxData = xDataInit;
    }
    TRACE("data load ok\r\n");
    return status_ok;
}

status_t DataSave(IN Data_t *pxData)
{

    /* Init FLASH data */
    Data_t xData;
    pxData->head = FLASH_DATA_HEAD;
    memcpy(&xData, pxData, sizeof(Data_t));
    xData.crc = prvCalcCrc((uint8_t *)&xData, sizeof(Data_t) - 1);
    MemFlashWrite(FLASH_SAVE_PAGE1, sizeof(Data_t), (uint8_t *)&xData);
    MemFlashWrite(FLASH_SAVE_PAGE2, sizeof(Data_t), (uint8_t *)&xData);

    return status_ok;
}

status_t DataSaveDirect(void)
{
    DataSave(&g_xData);
    return status_ok;
}

status_t data_save_direct(void)
{
    //DataSave(&g_xData);
    return status_ok;
}

static Bool_t prvChkCrc(uint8_t *pucData, uint16_t usLength)
{
    /* CRC */
    uint8_t tmp = prvCalcCrc(pucData, usLength - 1);
    return (pucData[usLength - 1] == tmp) ? TRUE : FALSE;
}

static uint8_t prvCalcCrc(uint8_t *pucData, uint16_t usLength)
{
    /* REFERENCE: https://www.devcoons.com/crc8/ */
    /* CRC-8/MAXIM */

    uint8_t crc = 0x00;
    uint8_t ucTmp, ucSum;

    for (uint16_t n = 0; n < usLength; n++)
    {
        ucTmp = pucData[n];
        for (uint8_t m = 0; m < 8; m++)
        {
            ucSum = (crc ^ ucTmp) & 0x01;
            crc >>= 1;
            if (ucSum)
            {
                crc ^= 0x8C;
            }
            ucTmp >>= 1;
        }
    }
    return crc;
}

static void prv_cli_cmd_cfg_show(cli_printf cliprintf, int argc, char **argv)
{
    CHECK_CLI();

    cliprintf("led_brightness        :  %d бы\r\n", th_led_brightness);
    cliprintf("led_color_temperature :  %d бы\r\n", th_led_color_temperature);
    cliprintf("led_status            :  %d\r\n", th_led_status);
    cliprintf("fan_polarity          :  %d\r\n", th_fan_polarity);
    cliprintf("fan_speed             :  %d %%\r\n", th_fan_speed);
    cliprintf("fan_status            :  %d\r\n", th_fan_status);
    cliprintf("\r\n");
}
CLI_CMD_EXPORT(cfg_show, show config parameters, prv_cli_cmd_cfg_show)
