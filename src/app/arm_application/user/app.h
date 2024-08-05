/*
	app.h

	Common Type Defines Head File For The Whole Project
*/

/* Copyright © 2024 Jasper. All rights reserved. */

/*
	modification history
	--------------------
	01a, 16May24, Jasper Created
*/
#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    extern uart_ctrl_t g_test_uart;

	void app_init(void);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*__APP_H */
