/**
 * @                                                    __----~~~~~~~~~~~------___
 * @                                   .  .   ~~//====......          __--~ ~~
 * @                   -.            \_|//     |||\\  ~~~~~~::::... /~
 * @                ___-==_       _-~o~  \/    |||  \\            _/~~-
 * @        __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~
 * @    _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /
 * @  .~       .~       |   \\ -_    /  /-   /   ||      \   /
 * @ /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /
 * @ |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\
 * @          '         ~-|      /|    |-~\~~       __--~~
 * @                      |-~~-_/ |    |   ~\_   _-~            /\
 * @                           /  \     \__   \/~                \__
 * @                       _--~ _/ | .-~~____--~-/                  ~~==.
 * @                      ((->/~   '.|||' -_|    ~~-/ ,              . _||
 * @                                 -_     ~\      ~~---l__i__i__i--~~_/
 * @                                 _-~-__   ~)  \----______________--~~
 * @                               //.-~~~-~_--~- |-------~~~~~~~~
 * @                                      //.-~~~--\
 * @                      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @
 * @                              神兽保佑            永无BUG
 **/

/*
    app.c

    Implementation File For The Whole Project
*/

/* Copyright © 2024 Jasper. ll rights reserved. */

/*
    modification history
    --------------------
    01a, 16May24, Jasper Created
*/

#include "app/arm_application/include.h"

#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)

/* Functions */
void app_init(void)
{
    debug_init();
    debug_uart_config(&huart1);
    debug_channel_set(DEBUG_CHAN_UART);
    app_cli_init();
    //breath_led_init();
    //lamp_init();
//    gyro_init();
//    ir_init();
    sys_init();

//    TRACE("hello world\r\n");
}
