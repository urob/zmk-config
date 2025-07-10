#include "layers.h"

/* aliases */
#define XXX &none
#define ___ &trans

/* keycode aliases */

// home row mods
#define _HOME_ROW_MODS_LEFT_   &hml LMETA A  &hml LALT S   &hml LSHFT D  &hml LCTRL F
#define _HOME_ROW_MODS_RIGHT_  &hmr RCTRL J  &hmr RSHFT K  &hmr LALT L   &hmr LMETA ;

// composite mod keys
#define MEH   LC(LA(LSHFT))
#define HYPER LC(LS(LG(LALT)))

// thumbs
#define FN_ESC   &lt FN ESCAPE
#define NUM_SPC  &lt NUM SPACE
#define CTL_TAB  &mt LCTRL TAB
// #define RTH3     &td_rth3
#define NUM_WORD &td_rth3

// #define NAV_KEY &mo NAV
//
#define NAV_KEY &mo_sk NAV LSHFT
#define BS_SFT  &th LSHIFT BACKSPACE

// left outer row keys
#define GRV_HYP &mt HYPER GRAVE
#define ESC_MEH &mt MEH ESC
#define CMP_SFT &mt LSHFT K_APP

// right outer row keys
#define BSL_HYP  &mt HYPER BACKSLASH
#define SLS_MEH  &mt MEH SLASH
#define RET_SFT  &mt LSHIFT RETURN

// 5 way joystick + encoder
#define _UP &kp UP
#define _L_ &kp LEFT
#define _R_ &kp RIGHT
#define _DN &kp DOWN
#define _PP &kp C_PP
#define _RT &kp RETURN

// edit
#define _UNDO &kp C_AC_UNDO
#define _CUT &kp C_AC_CUT
#define _COPY &kp C_AC_COPY
#define _PASTE &kp C_AC_PASTE
#define _REDO &kp C_AC_REDO

#define PS_BRK    &kp PAUSE_BREAK
#define PRINT_SCR &kp PAUSE_BREAK

// sys
#define _EP_OFF &ext_power EP_OFF
#define _EP_ON  &ext_power EP_ON

// BLE / OUTPUT
// management
#define TOG_OUT &out OUT_TOG
#define USB_OUT &out OUT_USB
#define BT_OUT  &out OUT_BLE
#define CLR_CH  &bt BT_CLR
#define CLR_ALL &bt BT_CLR_ALL


// channels
#define BT_CH0 &bt BT_SEL 0
#define BT_CH1 &bt BT_SEL 1
#define BT_CH2 &bt BT_SEL 2
#define BT_CH3 &bt BT_SEL 3
#define BT_CH4 &bt BT_SEL 4

// disconnect
#define BT_DISC0 &bt BT_DISC 0
#define BT_DISC1 &bt BT_DISC 1
#define BT_DISC2 &bt BT_DISC 2
#define BT_DISC3 &bt BT_DISC 3
#define BT_DISC4 &bt BT_DISC 4

// RGB
#define TOG_RGB &rgb_ug RGB_TOG
#define BRI_UP  &rgb_ug RGB_BRI // brightness up
#define BRI_DN  &rgb_ug RGB_BRD // brightness down
#define FX_NEXT &rgb_ug RGB_EFF // next rgb effect
#define FX_PREV &rgb_ug RGB_EFR // prev rgb effect
