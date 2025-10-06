#pragma once

#include <lvgl.h>
#include "util.h"

struct wpm_status_state {
    uint8_t wpm;
};

void draw_wpm_status(lv_obj_t *canvas, const struct status_state *state);