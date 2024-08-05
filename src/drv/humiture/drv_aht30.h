/*
    drv_aht30.h

    Implementation File For The aht30 moudle
*/

/* Copyright ? 2024 Jasper. All rights reserved. */

/*
    modification history
    --------------------
    01a, 21May24, Jasper Created
*/
#ifndef __AHT30_H
#define __AHT30_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "lib/type/lib_type.h"

    typedef enum
    {
        AHT30_STATUS_BUSY               = (1 << 7),        /**< busy bit */
        AHT30_STATUS_NOR_MODE           = (0 << 5),        /**< nor mode */
        AHT30_STATUS_CYC_MODE           = (1 << 5),        /**< cyc mode */
        AHT30_STATUS_CMD_MODE           = (2 << 5),        /**< cmd mode */
        AHT30_STATUS_CRC_FLAG           = (1 << 4),        /**< crc flag */
        AHT30_STATUS_CALIBRATION_ENABLE = (1 << 3),        /**< calibration enable */
        AHT30_STATUS_CMP_INT            = (1 << 2),        /**< comparation interrupt */
    } aht30_status_t;


    status_t aht30_init(void);
    status_t aht30_read_data(uint8_t *rx_buffer);
    status_t aht30_read_humiture(int *temperature, uint16_t *humidity);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
