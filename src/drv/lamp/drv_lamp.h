#ifndef __DRV_LAMP__
#define __DRV_LAMP__

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/type/lib_type.h"
#define   LAMP_DEBUG 1

void led_init(void);
void set_led_color(uint16_t color);
void set_led_brightness(uint16_t brightness);



#ifdef __cplusplus
}
#endif
#endif /*__DRV_LAMP__*/
