/*
	lib_delay_us.h

	Implementation file for delay module
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
	modification history
	--------------------
	01a, 18May24, Jasper Created
*/
#ifndef __DELAY_US_H
#define __DELAY_US_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include "stm32f1xx_hal.h"
#include "app/arm_application/config.h"

#if SORTWARE_I2C_ENABLE

	/* Defines */

	void sys_tick_init(void);
	void delay_us(uint32_t us);

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DELAY_US_H */
