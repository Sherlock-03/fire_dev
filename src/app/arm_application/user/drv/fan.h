/*
    fan.h
    Implementation File for fan Module
*/

/*
    modification history
    --------------------
    01a, 18May24, Jasper Created

*/
#ifndef __FAN_H
#define __FAN_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "stm32f1xx_hal.h"

    void fan_init(void);
    void prv_set_fan_pwm_duty(uint16_t fan_polarity, uint16_t fan_pwm_duty);
    void set_fan_speed(uint16_t fan_polarity, uint16_t fan_speed);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FAN_H */
