/* LAYERS */
#define DEF 0
#define NUM 1
#define NAV 2
#define FN 3
#define GAM 4
#define SYS 5

/* aliases */
#define XXX &none
#define ___ &trans

/* Global defaults */
#undef COMBO_TERM 
#define COMBO_TERM 25
#define QUICK_TAP_MS 180
#define TAPPING_TERM_MS 220
#define PRIOR_IDLE_MS 150

#undef COMBO_HOOK
#define COMBO_HOOK require-prior-idle-ms = <25>;

#ifdef CONFIG_WIRELESS
  #include <dt-bindings/zmk/bt.h>
  #include <dt-bindings/zmk/outputs.h>
  #define _CONN_MGMT_KEYS_ &out OUT_TOG    &out OUT_USB    &out OUT_BLE    &bt BT_CLR      &bt BT_CLR_ALL 
  #define _BT_SEL_KEYS_    &bt BT_SEL 0    &bt BT_SEL 1    &bt BT_SEL 2    &bt BT_SEL 3    &bt BT_SEL 4
  #define _BT_DISC_KEYS_   &bt BT_DISC 0   &bt BT_DISC 1   &bt BT_DISC 2   &bt BT_DISC 3   &bt BT_DISC 4
  #define _RGB_KEYS_       &rgb_ug RGB_TOG &rgb_ug RGB_EFR &rgb_ug RGB_EFF &rgb_ug RGB_BRI &rgb_ug RGB_BRD
#else
  #define _BT_SEL_KEYS_    ___ ___ ___ ___ ___
  #define _BT_MGMT_KEYS_   ___ ___ ___ ___ ___
  #define _CONN_MGMT_KEYS_ ___ ___ ___ ___ ___
#endif

/* keycode aliases */

// home row mods
#define _HOME_ROW_MODS_LEFT_   &hml LCTRL N  &hml LALT R   &hml LMETA T  &hml LSHFT S
#define _HOME_ROW_MODS_RIGHT_  &hmr RSHFT H  &hmr LMETA A  &hmr LALT E   &hmr LCTRL I

// composite mod keys
#define MEH   LC(LA(LSHFT))
#define HYPER LC(LS(LG(LALT)))

// thumbs
#define FN_ESC  &lt FN ESCAPE
#define NUM_SPC &lt NUM SPACE
#define CTL_TAB &mt LCTRL TAB

#define NAV_KEY &mo NAV 
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
