/*
	sys.h

	Common Type Defines Head File For The Whole Project
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
	modification history
	--------------------
	01a, 18May24, Jasper Created
*/
#ifndef __SYS_H
#define __SYS_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Includes */
#include "lib/type/lib_type.h"

/* Defines */
#define SYS_TASK_DELAY 20		 /* ms */
#define INFO_GET_TASK_DELAY 200 /* ms */

	status_t sys_init(void);

//	extern uint16_t led_status;
//	extern uint8_t led_brightness;
//	extern uint8_t led_color_temperature;
//	extern uint16_t fan_on_off, fan_level;

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* __SYS_H */
