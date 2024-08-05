/*
    led.c
    Implementation File for led Module
*/

/*
    modification history
    --------------------
    01a, 23Apr24, Jasper Created
    01b, 17May24, Jasper Modify the name of function

*/
#include "app/arm_application/include.h"

/* Debug config */
#if LED_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* LED_DEBUG */
#if LED_ASSERT
#undef ASSERT
#define ASSERT(a)                                                   \
    while (!(a))                                                    \
    {                                                               \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__); \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* LED_ASSERT */

/* global variables */
uint16_t g_last_led_brightness = 0, g_last_led_color_temperature = 0;

/* functions */
status_t led_init(void)
{
    /* You must initalize all parameters before you can operate a function */
    g_last_led_brightness = th_led_brightness;
    g_last_led_color_temperature = th_led_color_temperature;
    set_led_brightness(th_led_brightness);
    set_led_color_temperature(th_led_color_temperature);
    if (1 == th_led_status)
    {
        HAL_TIM_PWM_Start(LED_COLD_TIM, LED_COLD_TIM_CHANNEL);
        HAL_TIM_PWM_Start(LED_WARM_TIM, LED_WARM_TIM_CHANNEL);
    }

    return status_ok;
}

/* change pwm duty */
status_t prv_led_pwm_duty_ctrl(uint16_t led_cold_pwm_duty, uint16_t led_warm_pwm_duty)
{
    __HAL_TIM_SET_COMPARE(LED_COLD_TIM, LED_COLD_TIM_CHANNEL, led_cold_pwm_duty);
    __HAL_TIM_SET_COMPARE(LED_WARM_TIM, LED_WARM_TIM_CHANNEL, led_warm_pwm_duty);
    return status_ok;
}

/* change brightness */
status_t set_led_brightness(uint16_t led_brightness)
{
    g_last_led_brightness = led_brightness;
    uint16_t led_cold_brightness = 0, led_warm_brightness = 0;
    /* You can't change the color temperature when you adjust the brightness */
    led_warm_brightness = g_last_led_color_temperature * led_brightness / 1000;
    led_cold_brightness = (1000 - g_last_led_color_temperature) * led_brightness / 1000;
    prv_led_pwm_duty_ctrl(led_cold_brightness, led_warm_brightness);
    return status_ok;
}

/* change color temperature */
status_t set_led_color_temperature(uint16_t led_color_temperature)
{
    g_last_led_color_temperature = led_color_temperature;
    uint16_t led_cold_brightness = 0, led_warm_brightness = 0;
    /* You can't change the brightness when you adjust the color temperature */
    led_warm_brightness = led_color_temperature * g_last_led_brightness / 1000;
    led_cold_brightness = (1000 - led_color_temperature) * g_last_led_brightness / 1000;
    prv_led_pwm_duty_ctrl(led_cold_brightness, led_warm_brightness);
    return status_ok;
}

status_t set_night_light_status(uint16_t on_off)
{
    if (on_off != 1 && on_off != 0)
    {
        TRACE("night light on_off num error\r\n");
        return status_err;
    }
    HAL_GPIO_WritePin(LED_NIGHT_LIGHT_GPIO_PORT, LED_NIGHT_LIGHT_GPIO_PIN, (on_off ? GPIO_PIN_SET : GPIO_PIN_RESET));
    return status_ok;
}

status_t save_led_data(void)
{
    th_led_brightness = g_last_led_brightness;
    th_led_color_temperature = g_last_led_color_temperature;
    data_save_direct();
    return status_ok;
}

static void cli_set_led_brightness(cli_printf cliprintf, int argc, char **argv)
{
    if (2 == argc)
    {
        int led_brightness;
        led_brightness = atoi(argv[1]);
        if (led_brightness < 0 || led_brightness > 1000)
        {
            cliprintf("brightness : 0 - 1000\r\n");
            return;
        }
        set_led_brightness(led_brightness);
        save_led_data();
        refresh_screen(SET_LED_BR_ADDR, led_brightness / 10);
        cliprintf("set_led_brightness ok\r\n");
    }
    else
    {
        cliprintf("parameter length error\r\n");
    }
}
CLI_CMD_EXPORT(set_led_br, set led brightness, cli_set_led_brightness)

static void cli_set_led_color_temperature(cli_printf cliprintf, int argc, char **argv)
{
    if (2 == argc)
    {
        int led_color_temperature;
        led_color_temperature = atoi(argv[1]);
        if (led_color_temperature < 0 || led_color_temperature > 1000)
        {
            cliprintf("color_temperature : 0 - 1000\r\n");
            return;
        }
        set_led_color_temperature(led_color_temperature);
        save_led_data();
        refresh_screen(SET_LED_CT_ADDR, led_color_temperature / 10);
        cliprintf("led_color_temperature ok\r\n");
    }
    else
    {
        cliprintf("parameter length error\r\n");
    }
}
CLI_CMD_EXPORT(set_led_ct, set led color temperature, cli_set_led_color_temperature)

static void cli_set_night_light_status(cli_printf cliprintf, int argc, char **argv)
{
    if (2 == argc)
    {
        int on_off;
        on_off = atoi(argv[1]);
        if (on_off != 1 && on_off != 0)
        {
            cliprintf("on_off : 0 / 1\r\n");
            return;
        }
        set_night_light_status(on_off);
        cliprintf("set_night_light_status ok\r\n");
    }
    else
    {
        cliprintf("parameter length error\r\n");
    }
}
CLI_CMD_EXPORT(set_nl, set night light status, cli_set_night_light_status)
