/* 
 * helper.h
 *
 * Convenience macros simplifying ZMK's keymap configuration.
 * See https://github.com/urob/zmk-nodefree-config for documentation.
 */

#pragma once

#define ZMK_HELPER_STRINGIFY(x) #x

/* ZMK_BEHAVIOR */

#define ZMK_BEHAVIOR_CORE_caps_word   compatible = "zmk,behavior-caps-word";  #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_hold_tap    compatible = "zmk,behavior-hold-tap";   #binding-cells = <2>
#define ZMK_BEHAVIOR_CORE_key_repeat  compatible = "zmk,behavior-key-repeat"; #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_macro       compatible = "zmk,behavior-macro";      #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_mod_morph   compatible = "zmk,behavior-mod-morph";  #binding-cells = <0>
#define ZMK_BEHAVIOR_CORE_sticky_key  compatible = "zmk,behavior-sticky-key"; #binding-cells = <1>
#define ZMK_BEHAVIOR_CORE_tap_dance   compatible = "zmk,behavior-tap-dance";  #binding-cells = <0>

#define ZMK_BEHAVIOR(name, type, ...) \
    / { \
        behaviors { \
            name: name { \
                label = ZMK_HELPER_STRINGIFY(ZB_ ## name); \
                ZMK_BEHAVIOR_CORE_ ## type; \
                __VA_ARGS__ \
            }; \
        }; \
    };

/* ZMK_LAYER */

#define ZMK_LAYER(name, layout) \
    / { \
        keymap { \
            compatible = "zmk,keymap"; \
            name { \
                bindings = <layout>; \
            }; \
        }; \
    };

/* ZMK_COMBOS */

#define ALL -1
#if !defined COMBO_TERM
    #define COMBO_TERM 30
#endif

#define COMBO(name, combo_bindings, keypos, combo_layers) \
    / { \
        combos { \
            compatible = "zmk,combos"; \
            combo_ ## name { \
                timeout-ms = <COMBO_TERM>; \
                bindings = <combo_bindings>; \
                key-positions = <keypos>; \
                layers = <combo_layers>; \
            }; \
        }; \
    };

/* ZMK_UNICODE */

#if !defined OS_COMBO_LEAD
    #if HOST_OS == 2
        // OSx
    #elif HOST_OS == 1 
        // Linux
    #else
        #define OS_COMBO_LEAD &kp RALT &kp U  // Windows + WinCompose (default)
    #endif
#endif
#if !defined OS_COMBO_TRAIL
    #if HOST_OS == 2
        // OSx
    #elif HOST_OS == 1 
        // Linux
    #else
        #define OS_COMBO_TRAIL &kp RET  // Windows + WinCompose (default)
    #endif
#endif

#define UC_MACRO(name, unicode_bindings) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                label = ZMK_HELPER_STRINGIFY(UC_MACRO_ ## name); \
                wait-ms = <0>; \
                tap-ms = <1>; \
                #binding-cells = <0>; \
                bindings = <OS_COMBO_LEAD>, <unicode_bindings>, <OS_COMBO_TRAIL>; \
            }; \
        }; \
    };

#define UC_MODMORPH(name, uc_binding, shifted_uc_binding) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                label = ZMK_HELPER_STRINGIFY(UC_MORPH_ ## name); \
                #binding-cells = <0>; \
                bindings = <uc_binding>, <shifted_uc_binding>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
                masked_mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };

#define ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3) \
    UC_MACRO(uc_lower_ ## name, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MODMORPH(uc_ ## name, &uc_lower_ ## name, &none)

#define ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3) \
    UC_MACRO(uc_lower_ ## name, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MACRO(uc_upper_ ## name, &kp U0 &kp U1 &kp U2 &kp U3) \
    UC_MODMORPH(uc_ ## name, &uc_lower_ ## name, &uc_upper_ ## name)

