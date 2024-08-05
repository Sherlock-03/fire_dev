/*
    led.h
    Implementation File for led Module
*/

/*
    modification history
    --------------------
    01a, 23Apr24, Jasper Created
    01b, 17May24, Jasper Modify the name of function

*/
#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "stm32f1xx_hal.h"
#include "lib/type/lib_type.h"

    extern uint16_t g_last_led_brightness;
    extern uint16_t g_last_led_color_temperature;

    status_t led_init(void);
    status_t set_led_brightness(uint16_t led_brightness);
    status_t set_led_color_temperature(uint16_t led_color_temperature);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LED_H */
