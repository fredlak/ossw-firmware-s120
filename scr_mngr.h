#ifndef SCR_MNGR_H
#define SCR_MNGR_H

#include <stdbool.h>
#include <stdint.h>

#define SCR_WATCHFACE                0x01
#define SCR_CHANGE_DATE              0x02
#define SCR_CHANGE_TIME              0x03

#define SCR_EVENT_INIT_SCREEN        0x01
#define SCR_EVENT_BUTTON_PRESSED     0x11
#define SCR_EVENT_RTC_TIME_CHANGED   0x12

void scr_mngr_init(void);

void scr_mngr_handle_event(uint32_t event_type, uint32_t event_param);

void scr_mngr_show_screen(uint32_t screen_id);

#endif /* SCR_MNGR_H */
