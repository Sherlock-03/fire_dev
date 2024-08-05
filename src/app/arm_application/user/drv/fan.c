/*
    fan.c
    Implementation File for led Module
*/

/*
    modification history
    --------------------
    01a, 23Apr24, Jasper Created
    01b, 17May24, Jasper Modify the name of function

*/
/* Includes */
#include "app/arm_application/include.h"


void fan_init(void)
{
    /* You must initalize all parameters before you can operate a function */
    set_fan_speed(th_fan_polarity, th_fan_speed);
    if (1 == th_fan_status)
    {
        HAL_TIM_PWM_Start(FAN_FORWARD_TIM, FAN_FORWARD_CHANNEL);
        //HAL_TIM_PWM_Start(FAN_REVERSE_TIM, FAN_REVERSE_CHANNEL);
    }
}

/* set pwm duty */
void prv_set_fan_pwm_duty(uint16_t fan_polarity, uint16_t fan_pwm_duty)
{
    if (fan_polarity == 1)
    {
        __HAL_TIM_SET_COMPARE(FAN_FORWARD_TIM, FAN_FORWARD_CHANNEL, fan_pwm_duty);
        __HAL_TIM_SET_COMPARE(FAN_REVERSE_TIM, FAN_REVERSE_CHANNEL, 0);
    }
    else if (fan_polarity == 0)
    {
        __HAL_TIM_SET_COMPARE(FAN_FORWARD_TIM, FAN_FORWARD_CHANNEL, 0);
        __HAL_TIM_SET_COMPARE(FAN_REVERSE_TIM, FAN_REVERSE_CHANNEL, fan_pwm_duty);
    }
}

/* set fan speed */
void set_fan_speed(uint16_t fan_polarity, uint16_t fan_speed)
{
    if (th_fan_polarity != fan_polarity || th_fan_speed != fan_speed)
    {
        th_fan_polarity = fan_polarity;
        th_fan_speed = fan_speed;
        data_save_direct();
    }
    
    /* fan speed -> fan pwm duty */
    uint16_t fan_pwm_duty = fan_speed;

    /* set fan pwm duty */
    prv_set_fan_pwm_duty(fan_polarity, fan_pwm_duty);
}

static void cli_set_fan_speed(cli_printf cliprintf, int argc, char **argv)
{
    if (3 == argc)
    {
        int fan_polarity = 0, fan_speed = 0;

        fan_polarity = atoi(argv[1]);
        fan_speed = atoi(argv[2]);

        if (fan_polarity != 1 && fan_polarity != 0)
        {
            cliprintf("polarity : 0 / 1\r\n");
            return;
        }

        if (fan_speed < 0 || fan_speed > 100)
        {
            cliprintf("fan_speed : 0 - 100");
            return;
        }

        set_fan_speed(fan_polarity, fan_speed);
        cliprintf("set_fan_speed ok\r\n");
    }
    else
    {
        cliprintf("parameter length error\r\n");
    }
}
CLI_CMD_EXPORT(set_fan_speed, set fan speed, cli_set_fan_speed)
