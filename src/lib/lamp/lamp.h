#ifndef __LAMP__
#define  __LAMP__

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/type/lib_type.h"
#define   LAMP_DEBUG 1

status_t lamp_init(void);
void led_color();



#ifdef __cplusplus
}
#endif
#endif /*__LAMP__*/
