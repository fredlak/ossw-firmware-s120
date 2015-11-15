#include <string.h>
#include "scr_watchface.h"
#include "../scr_mngr.h"
#include "../rtc.h"
#include "../mlcd.h"
#include "../scr_controls.h"
#include "../vibration.h"
#include "../watchset.h"
#include "../fs.h"
#include "nrf_delay.h"
		
static NUMBER_CONTROL_DATA hour_ctrl_data;
		
static const SCR_CONTROL_NUMBER_CONFIG hour_config = {
		NUMBER_RANGE_0__99,
	  4,
	  4,
	  NUMBER_FORMAT_FLAG_ZERO_PADDED | 4 << 24 | 8 << 16 | 66 << 8 | 76,
	  (uint32_t (*)(uint32_t, uint8_t))rtc_get_current_hour_24,
	  0,
		NULL,
    &hour_ctrl_data
};

static NUMBER_CONTROL_DATA minutes_ctrl_data;

static const SCR_CONTROL_NUMBER_CONFIG minutes_config = {
		NUMBER_RANGE_0__99,
	  4,
	  85,
	  NUMBER_FORMAT_FLAG_ZERO_PADDED | 4 << 24 | 6 << 16 | 66 << 8 | 76,
	  (uint32_t (*)(uint32_t, uint8_t))rtc_get_current_minutes,
	  0,
		NULL,
    &minutes_ctrl_data
};

static NUMBER_CONTROL_DATA seconds_ctrl_data;

static const SCR_CONTROL_PROGRESS_BAR_CONFIG seconds_config = {
	  0,
	  MLCD_YRES - 3,
	  MLCD_XRES,
	  2,
	  60,
		0,
	  rtc_get_current_seconds,
	  0,
		NULL,
    &seconds_ctrl_data
};

static const SCR_CONTROL_DEFINITION controls[] = {
	  {SCR_CONTROL_NUMBER, (void*)&hour_config},
		{SCR_CONTROL_NUMBER, (void*)&minutes_config},
		{SCR_CONTROL_PROGRESS_BAR, (void*)&seconds_config}
};

static const SCR_CONTROLS_DEFINITION controls_definition = {
	  sizeof(controls)/sizeof(SCR_CONTROL_DEFINITION),
	  (SCR_CONTROL_DEFINITION*)controls
};

static void scr_watchface_refresh_time() {
	  scr_controls_redraw(&controls_definition);
}

static void scr_watchface_init() {
	  spiffs_file fd = watchset_get_dafault_watch_face_fd();
		if (fd >= 0) {
				SPIFFS_lseek(&fs, fd, 0, SPIFFS_SEEK_SET);
				scr_mngr_show_screen_with_param(SCR_WATCH_SET, 2<<24 | fd);
		}
}

static void scr_watchface_draw() {
	  scr_controls_draw(&controls_definition);
}

void scr_watchface_handle_event(uint32_t event_type, uint32_t event_param) {
    switch(event_type) {
        case SCR_EVENT_INIT_SCREEN:
            scr_watchface_init();
            break;
        case SCR_EVENT_DRAW_SCREEN:
            scr_watchface_draw();
            break;
        case SCR_EVENT_REFRESH_SCREEN:
            scr_watchface_refresh_time();
            break;
    }
		watchset_default_watch_face_handle_event(event_type, event_param);
}
