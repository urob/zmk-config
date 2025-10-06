#pragma once

#include <lvgl.h>
#include <zmk/endpoints.h>
#include "util.h"

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
struct output_status_state {
    struct zmk_endpoint_instance selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
};
#else
struct peripheral_status_state {
    bool connected;
};
#endif

void draw_output_status(lv_obj_t *canvas, const struct status_state *state);