// Auto Layer
ZMK_BEHAVIOR(num_word, auto_layer,
    continue-list = <BSPC DEL KP_DOT DOT COMMA KP_PLUS PLUS KP_MINUS MINUS KP_MULTIPLY STAR KP_DIVIDE FSLH EQUAL>;
    ignore-numbers;
)
ZMK_BEHAVIOR(mouse_word, auto_layer,
    continue-list = <PG_DN PG_UP SCRL_LEFT SCRL_RIGHT SCRL_DOWN SCRL_UP LCLK RCLK MCLK MOVE_LEFT MOVE_RIGHT MOVE_UP MOVE_DOWN>;
    ignore-numbers;
)
ZMK_BEHAVIOR(nav_word, auto_layer,
    continue-list = <SCRL_LEFT SCRL_RIGHT SCRL_DOWN SCRL_UP LCLK RCLK MCLK MOVE_LEFT MOVE_RIGHT MOVE_UP MOVE_DOWN LEFT DOWN UP RIGHT PG_DN PG_UP HOME END ENTER BACKSPACE DEL>;
    ignore-numbers;
)
ZMK_BEHAVIOR(wm_word, auto_layer,
    continue-list = <F13 F14 F15 F22 F17 F18 F19 F20 F21 F22>;
    ignore-numbers;
)

// Mod Morph
ZMK_BEHAVIOR(backspace_delete, mod_morph,
    bindings = <&kp BACKSPACE>, <&kp DELETE>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
    keep-mods = <(MOD_RSFT)>;
)

// Tap Dance
ZMK_BEHAVIOR(tap_dot_shift, tap_dance,
    tapping-term-ms = <250>;
    bindings = <&kp DOT>, <&macro_dot_shift>;
)
ZMK_BEHAVIOR(tap_paste, tap_dance,
    tapping-term-ms = <250>;
    bindings = <&kp LC(V)>, <&kp LC(LS(V))>;
)
ZMK_BEHAVIOR(tap_copy_cut, tap_dance,
    tapping-term-ms = <250>;
    bindings = <&kp LC(C)>, <&kp LC(X)>;
)
ZMK_BEHAVIOR(tap_dot_shift_capsword, tap_dance,
    tapping-term-ms = <250>;
    bindings = <&as_dot_shift 0 DOT>, <&macro_dot_shift>, <&caps_word>;
)
ZMK_BEHAVIOR(tap_sk_shift_dot_caps_word_lt, tap_dance,
    tapping-term-ms = <350>;
    bindings = <&sk LSHIFT>, <&macro_dot_shift>, <&caps_word>;
)

// Hold-Taps
ZMK_BEHAVIOR(smart_num, hold_tap,
    bindings = <&mo>, <&num_word>;
    tapping-term-ms = <175>;
    flavor = "balanced";
    hold-trigger-key-positions = <41>;
    quick-tap-ms = <150>;
    hold-while-undecided;
)
ZMK_BEHAVIOR(mo_dot_shift, hold_tap,
    bindings = <&macro_dot_shift>, <&kp>;
    tapping-term-ms = <250>;
    quick-tap-ms = <200>;
    flavor = "tap-preferred";
    require-prior-idle-ms = <150>;
    hold-trigger-on-release;
)
ZMK_BEHAVIOR(hmr_clk, hold_tap,
    bindings = <&hmr>, <&mkp>;
    tapping-term-ms = <250>;
    quick-tap-ms = <200>;
    flavor = "tap-preferred";
    require-prior-idle-ms = <150>;
)
ZMK_BEHAVIOR(tap_key_repeat_lt, hold_tap,
    bindings = <&mo>, <&key_repeat>;
    tapping-term-ms = <225>;
    quick-tap-ms = <175>;
    flavor = "balanced";
    require-prior-idle-ms = <50>;
)
ZMK_BEHAVIOR(kp_to, hold_tap,
    bindings = <&to>, <&kp>;
    tapping-term-ms = <175>;
    quick-tap-ms = <175>;
    flavor = "balanced";
    require-prior-idle-ms = <50>;
)
ZMK_BEHAVIOR(mod_to0_mouse_jiggle, hold_tap,
    bindings = <&macro_mouse_jiggle>, <&kp>;
    tapping-term-ms = <225>;
    quick-tap-ms = <175>;
    flavor = "tap-preferred";
    require-prior-idle-ms = <50>;
)
ZMK_BEHAVIOR(tap_key_repeat_to, hold_tap,
    bindings = <&to>, <&key_repeat>;
    tapping-term-ms = <225>;
    quick-tap-ms = <175>;
    flavor = "balanced";
    require-prior-idle-ms = <50>;
)
ZMK_BEHAVIOR(macro_dot_shift_lt, hold_tap,
    bindings = <&lt>, <&macro_dot_shift>;
    tapping-term-ms = <225>;
    quick-tap-ms = <175>;
    flavor = "balanced";
    require-prior-idle-ms = <50>;
)
ZMK_BEHAVIOR(shift_mod, hold_tap,
    bindings = <&kp>, <&kp>;
    tapping-term-ms = <125>;
    quick-tap-ms = <150>;
    flavor = "balanced";
    require-prior-idle-ms = <0>;
    hold-trigger-key-positions = <14 15 16 17 0 1 13 26 27 28 29 31 5 2 3 4 18 23 45 46 44 30 33 20 7 8 21 34 22 9 35 36 37 38 25 24 11 12 10 41 42 40 39 19 32 47 43 6>;
)
ZMK_BEHAVIOR(as_dot_shift, hold_tap,
    bindings = <&mo_dot_shift>, <&kp>;
    tapping-term-ms = <175>;
    flavor = "balanced";
)
ZMK_BEHAVIOR(tap_key_repeat_sk_shift, hold_tap,
    bindings = <&sk>, <&key_repeat>;
    tapping-term-ms = <150>;
    quick-tap-ms = <150>;
    flavor = "balanced";
    require-prior-idle-ms = <50>;
    hold-trigger-key-positions = <0 1 14 27 2 3 4 5 15 16 17 18 28 29 30 31 6 19 43 47 32 7 8 9 10 11 12 20 21 22 23 24 25 33 34 35 36 37 38>;
)
ZMK_BEHAVIOR(sk_shift_dot_shift, hold_tap,
    bindings = <&macro_dot_shift>, <&sk>;
    tapping-term-ms = <250>;
    flavor = "tap-preferred";
    quick-tap-ms = <200>;
)
ZMK_BEHAVIOR(mo_num_word, hold_tap,
    bindings = <&num_word>, <&kp>;
    tapping-term-ms = <175>;
    flavor = "tap-preferred";
    quick-tap-ms = <150>;
)
ZMK_BEHAVIOR(tap_key_repeat_wm_word, hold_tap,
    bindings = <&wm_word>, <&key_repeat>;
    tapping-term-ms = <175>;
    quick-tap-ms = <150>;
    require-prior-idle-ms = <150>;
    flavor = "tap-preferred";
)
ZMK_BEHAVIOR(mo_nav_word, hold_tap,
    bindings = <&nav_word>, <&kp>;
    flavor = "balanced";
    tapping-term-ms = <175>;
    quick-tap-ms = <150>;
)
ZMK_BEHAVIOR(lt_num_word, hold_tap,
    bindings = <&mo>, <&num_word>;
    tapping-term-ms = <175>;
    flavor = "tap-preferred";
    quick-tap-ms = <150>;
)
ZMK_BEHAVIOR(lt_nav_word, hold_tap,
    bindings = <&mo>, <&nav_word>;
    tapping-term-ms = <175>;
    flavor = "tap-preferred";
    quick-tap-ms = <150>;
)
ZMK_BEHAVIOR(kp_msc, hold_tap,
    bindings = <&msc>, <&kp>;
    tapping-term-ms = <175>;
    flavor = "balanced";
    quick-tap-ms = <150>;
    hold-trigger-key-positions = <21 22 23 24 45>;
    require-prior-idle-ms = <150>;
)
ZMK_BEHAVIOR(tap_repeat_mouse_word, hold_tap,
    bindings = <&mouse_word>, <&key_repeat>;
    tapping-term-ms = <175>;
    quick-tap-ms = <150>;
    require-prior-idle-ms = <150>;
    flavor = "tap-preferred";
)
ZMK_BEHAVIOR(smart_sk_lt, hold_tap,
    bindings = <&lt>, <&tap_sk_shift_dot_caps_word_lt>;
    tapping-term-ms = <500>;
    quick-tap-ms = <450>;
    flavor = "balanced";
    hold-trigger-key-positions = <0 1 2 3 4 5 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 6>;
)