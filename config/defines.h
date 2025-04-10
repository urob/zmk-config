/* LAYERS */
#define DEF 0
#define NUM 1
#define NAV 2
#define GAM 3
#define FN 4
#define SYS 5
#define MOUSE 6

/* aliases */
#define XXX &none
#define ___ &trans

/* Global defaults */
#undef COMBO_TERM 
#define COMBO_TERM 25
#define QUICK_TAP_MS 175
#define TAPPING_TERM_MS 220
#define PRIOR_IDLE_MS 175

#undef COMBO_HOOK
#define COMBO_HOOK require-prior-idle-ms = <25>;

