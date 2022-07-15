# zmk-nodefree-config

ZMK lets user customize their keyboard layout by providing a Devicetree file
(`.keymap`). The specific syntax requirements of the Devicetree file format can,
however, make this process a bit daunting for new users. 

This repository provides simple convenience macros that simplify the configuration for
many common use cases. It results in a "node-free" user configuration with a more
streamlined syntax. Check out [example.keymap](example.keymap) to see it in action.

## Overview

The following convenience macros are provided:
1. `ZMK_BEHAVIOR` can be used to create new behaviors such as hold-taps, tap-dances or
   ZMK macros [\[doc\]](#zmk_behavior)
2. `ZMK_LAYER` adds new layers to your keymap [\[doc\]](#zmk_layer)
3. `ZMK_COMBO` defines new combos [\[doc\]](#zmk_combo)
4. `ZMK_CONDITIONAL_LAYERS` sets up "tri-layer" conditions [\[doc\]](#zmk_conditional_layers)
5. `ZMK_UNICODE_SINGLE` and `ZMK_UNICODE_PAIR` create unicode characters [\[doc\]](#zmk_unicode)
6. optional `international_chars` source files define a number of international character such
   as <kbd>ä</kbd>/<kbd>Ä</kbd> or <kbd>δ</kbd>/<kbd>Δ</kbd> that can be added to the keymap
   [\[doc\]](#international-characters)
7. optional `keypos_def` source files define human-readable key position shortcuts for some popular
   keyboards that simplify the configuration of combos and positional hold-taps
   [\[doc\]](#key-position-shortcuts)

## Quickstart

1. Copy this repository into the root folder of your private zmk-config repository. The
   folder structure should look as follows:
   ```
    zmk-config
     ├── config
     │    ├── your.keyboard.conf
     │    ├── your_keyboard.keymap
     │    └── ...
     ├── zmk-nodefree-config
     │    ├── helper.h
     │    ├── ...
   ```
2. Source `helper.h` near the top of your `.keymap` file:
    ```C++
    #include "../zmk-nodefree-config/helper.h"
    ```
3. Customize your keyboard's `.keymap` file. See [example.keymap](example.keymap) or [my
   personal zmk-config](https://github.com/urob/zmk-config/blob/main/config/base.keymap)
   for a complete configuration, and read the documentation below for details.

## Configuration details

### ZMK\_BEHAVIOR

`ZMK_BEHAVIOR` can be used to create any of the following ZMK behaviors: caps-word,
hold-tap, key-repeat, macro, mod-morph, sticky-key or tap-dance

**Syntax:** `ZMK_BEHAVIOR(name, type, specification)`
* `name`: a unique string chosen by the user (e.g., `my_behavior`). The new behavior can
  be added to the keymap using `&name` (e.g., `&my_behavior`)
* `type`: the behavior to be created. It must be one of the following:
  `caps_word`, `hold_tap`, `key_repeat`, `macro`, `mod_morph`, `sticky_key` or
  `tap_dance`. Note that two-word types are separated by underscores (`_`).
* `specification`: the custom behavior code. It should contain the
  body of the corresponding [ZMK behavior configuration](https://zmk.dev/docs/config/behaviors)
  without the `label`, `#binding-cells` and `compatible` properties and without the
  surrounding node-specification.

#### Example 1: Creating a custom "homerow mod" tap-hold behavior

```C++
ZMK_BEHAVIOR(hrm, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    global-quick-tap;
    bindings = <&kp>, <&kp>;
)
```

The new behavior can be added to the keymap-layout using `&hrm` (e.g., `&hrm LSHIFT T`
creates a key that yields `T` on tap and `LSHIFT` on hold, using the custom
configuration above).

#### Example 2: Creating a custom tap-dance key

```C++
ZMK_BEHAVIOR(ss_cw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&sk LSHFT>, <&caps_word>;
)
```

The new behavior can be added to the keymap-layout using `&ss_cw`. The key yields 
sticky-shift on tap and caps-word on double tap;

#### Example 3: Creating a custom "win-sleep" macro

```C++
ZMK_BEHAVIOR(win_sleep, macro,
    wait-ms = <100>;
    tap-ms = <5>;
    bindings = <&kp LG(X) &kp U &kp S>;
)
```

This creates a "Windows sleep key" that can be added to the keymap-layout using
`&win_sleep`.

### ZMK\_LAYER

`ZMK_LAYER` adds new keymap layers to the configuration.

**Syntax:** `ZMK_LAYER(name, layout)`
* `name`: a unique identifier string chosen by the user (usually this isn't referenced elsewhere)
* `layout`: the layout specification using the same syntax as the `bindings`
  property of the [ZMK keymap configuration](https://zmk.dev/docs/config/keymap)

Multiple layers can be added with repeated calls of `ZMK_LAYER`. They will be ordered
in the same order in which they are created, with the first-specified layer being
the "lowest" one ([see here for details](https://zmk.dev/docs/features/keymaps#layers)).

#### Example usage
```C++
ZMK_KEYMAP(default_layer,
     // ╭─────────────┬─────────────┬─────────────┬─────────────┬─────────────╮   ╭─────────────┬─────────────┬─────────────┬─────────────┬─────────────╮
          &kp Q         &kp W         &kp F         &kp P         &kp B             &kp J         &kp L         &kp U         &kp Y         &kp SQT
     // ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
          &hrm LGUI A   &hrm LALT R   &hrm LCTRL S  &hrm LSHFT T  &kp G             &kp M         &hrm RSHFT N  &hrm LCTRL E  &hrm LALT I   &hrm LGUI O
     // ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
          &kp Z         &kp X         &kp C         &kp D         &kp V             &kp K         &kp H         &kp COMMA     &kp DOT       &kp SEMI
     // ╰─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
                                      &kp ESC       &lt NAV SPACE &kp TAB           &kp RET       &ss_cw        &bs_del_num
     //                             ╰─────────────┴──── ────────┴─────────────╯   ╰─────────────┴─────────────┴─────────────╯
)

```

### ZMK\_COMBO

`ZMK_COMBO` defines new combos.

**Syntax:** `ZMK_COMBO(name, bindings, keypos, layers)`
* `name`: a unique identifier string chosen by the user (usually this isn't referenced elsewhere)
* `binding`: the binding triggered by the combo (this can be any stock or previously defined behavior)
* `keypos`: a list of 2 or more key positions that trigger the combo (e.g., `12
  13`). Note that the mapping from key positions to keys depends on your keyboard. To facilitate 
  the combo set-up and increase portability, this repository provides shortcuts for some popular keyboards.
  See [below](#key-position-shortcuts) on how to use them.
* `layers`: a list of layers for which the combo is active (e.g., `0 1` for the first
  two layers). If set to `ALL` the combo is active on all layers.

By default, the timeout for combos created with `ZMK_COMBO` is 30ms. If `COMBO_TERM` is
set prior to calling `ZMK_COMBO`, the value of `COMBO_TERM` is used instead. Note: while
it is possible to set different timeout for different combos, this is known to cause
[issues](https://github.com/zmkfirmware/zmk/issues/905) with overlapping combos and should be avoided.

#### Example: copy and paste combos

```C++
#define COMBO_TERM 50
ZMK_COMBO(copy,  &kp LC(C), 12 13, ALL)
ZMK_COMBO(paste, &kp LC(V), 13 14, ALL)
```
This sets the combo timeout to 50ms, and then creates two combos which both are 
active all layers. The first combo is triggered when the
12th and 13th keys are pressed jointly within the `COMBO_TERM`, sending <kbd>Ctrl</kbd> + <kbd>C</kbd>. The
second combo is triggered when the 13th and 14th keys are pressed jointly, sending
<kbd>Ctrl</kbd> + <kbd>V</kbd>.

### ZMK\_CONDITIONAL\_LAYERS

This sets up tri-layer conditions.

**Syntax:** `ZMK_CONDITIONAL_LAYERS(if_layers, then_layers)`
* `if_layers`: a list of layers which trigger the `then_layer` if simultaneously active
* `then_layer`: the layer which is activated when the if-condition is met. Due to ZMK's
  layering model, it should generally have a higher number than the `if_layers`

For instance, this triggers "layer 3" if layers "1" and "2" are
simultaneously active. 
```C++
ZMK_CONDITIONAL_LAYERS(1 2, 3)
```
Mind that ZMK's layer numbering starts at 0! In general, it is recommended to use layer
definitions, as demonstrated in [example.keymap](example.keymap), to simplify life.

### ZMK\_UNICODE

There are two macros that simplify creating new unicode characters that
can be added to the keymap. `ZMK_UNICODE_SINGLE` creates single unicode characters such
as <kbd>€</kbd>, whereas `ZMK_UNICODE_PAIR` creates pairs of shifted/unshifted unicode
characters that are useful for specifying international characters such as
<kbd>ä</kbd>/<kbd>Ä</kbd> or <kbd>δ</kbd>/<kbd>Δ</kbd>.

Note that the input of unicode characters differs across operation systems. By default,
`ZMK_UNICODE` is configured for Windows (using WinCompose). The easiest way to set up unicode
characters for other operation systems is to set the variable `HOST_OS` **before**
sourcing `helper.h`.

For Linux use:
```C++
#define HOST_OS 1  // set to 1 for Linux, default is 0 (Windows)
#include helper.h
```
For macOS use:
```C++
#define HOST_OS 2  // set to 2 for macOS, default is 0 (Windows)
#include helper.h
```
This will send unicode characters using the OS's default input channels.
For non-default input channels or for other operation systems, one can instead set the
variables `OS_UNICODE_LEAD` and `OS_UNICODE_TRAIL` to the character sequences that
initialize/terminate the unicode input.

**Syntax:** `ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3)`
* `name:` a unique string chosen by the user (e.g., `my_char`). The unicode character  can
  be added to the keymap using `&name` (e.g., `&my_char`)
* `L0` to `L3`: a 4-digit sequence defining the unicode string using standard [ZMK key
  codes](https://zmk.dev/docs/codes/keyboard-keypad)

**Syntax:** `ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3)`
* `name:` a unique string chosen by the user (e.g., `my_char`). The unicode character  can
  be added to the keymap using `&name` (e.g., `&my_char`)
* `L0` to `L3`: a 4-digit sequence defining the unshifted unicode string
* `U0` to `U3`: a 4-digit sequence defining the shifted unicode string (which is send when
  holding <kbd>Shift</kbd> while pressing <kbd>&name</kbd>)

Note: 5-digit unicode characters are currently not supported.

#### Example 1: Euro sign (U+20AC)

```C++
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)
```
The Euro character can be added to the keymap using `&euro_sign`.

#### Example 2: German umlauts (ä/Ä, ö/Ö, ü/Ü)

```C++
//                name  unshifted         shifted
ZMK_UNICODE_PAIR( ae,   N0, N0,  E, N4,   N0, N0,  C, N4 )
ZMK_UNICODE_PAIR( oe,   N0, N0,  F, N6,   N0, N0,  D, N6 )
ZMK_UNICODE_PAIR( ue,   N0, N0,  F,  C,   N0, N0,  D,  C )
```
The "umlaut"-pairs can be added to the keymap using `&ae`, `&oe` and `&ue`.

#### Dependencies for unicodes

* `ZMK_UNICODE_PAIR` requires a ZMK version patched with
  [PR#1114](https://github.com/zmkfirmware/zmk/pull/1114) (not needed for
  `ZMK_UNICODE_SINGLE`). If you don't want to maintain
  your own ZMK repository, you can use ZMK's [beta
  testing](https://zmk.dev/docs/features/beta-testing) feature to configure Github
  Actions to build against a patched remote branch of ZMK. To do so, replace the
  contents of `west.yml` in your local `zmk-config/config` directory with the following
  contents:
    ```
    manifest:
      remotes:
        - name: urob
          url-base: https://github.com/urob
      projects:
        - name: zmk
          remote: urob
          revision: masked-mods
          import: app/west.yml
      self:
        path: config
    ```
* Depending on the operation system there are addition requirements for unicode input to
  work. On Windows, one must install
  [WinCompose](https://github.com/samhocevar/wincompose). On macOS one must enable
  unicode input in the system preferences.

### International characters

There are pre-defined definitions for international characters for a few
languages (currently German and Greek --- contributions are welcome!). These can be
loaded by sourcing the corresponding files.
```C++
#include "../zmk-nodefree-config/international_chars/greek.dtsi"
#include "../zmk-nodefree-config/international_chars/german.dtsi"
```
These definitions make use of unicode in the background, please see the unicode documentation
above for prerequisites. Once sourced, Greek and German characters can be added to the
keymap using, e.g., `&alpha`, `&upsilon`, `&tau` or `&omikron` (see the language files for
a complete list of available characters).

### Key position shortcuts

Certain configuration options such as combos and positional hold-taps are based on the 
physical position of keys on your keyboard. This reduces portability of configuration
files across keyboards with different layouts. 

To increase portability, this repository comes with key position definitions for some
popular keyboard layouts (48-key boards such as Planck, 42-key boards such as Corne,
36-key boards and 34-key boards).

These layouts provide a map from the physical key positions to human-readable shortcuts.
All shortcuts are of the following form:
* `L/R` for **L**eft/**R**ight hand
* `T/M/B/H` for **T**op/**M**iddle/**B**ottom and t**H**umb row.
* `0/1/2/3/4` for the finger position starting from the inside (`0` is the inner
  index-finger column, `1` is the home position of the index finger, ..., `4` is the home
  position of the pinkie)

For instance, the shortcuts layout for a 36-key board looks as follows:
```
╭─────────────────────┬─────────────────────╮
│ LT4 LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 RT4 │
│ LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 │
│ LB4 LB3 LB2 LB1 LB0 │ RB0 RB1 RB2 RB3 RB4 │
╰───────╮ LH2 LH1 LH0 │ RH0 RH1 RH2 ╭───────╯
        ╰─────────────┴─────────────╯
```
Schematics for all existing layout files can be found at the top of the corresponding
definition files.

To use these shortcut definitions, source the definition file for your keyboard
into your `.keymap` file. E.g., for a 36-key board, use:
```C++
#include "../zmk-nodefree-config/keypos_def/keypos_36keys.h"
```

#### Example 1: Defining combos using key position shortcuts

```C++
ZMK_COMBO(copy,  &kp LC(C), LB2 LB3, ALL)
ZMK_COMBO(paste, &kp LC(V), LB1 LB2, ALL)
```

This defines a "copy"-combo for the middle + ring finger on the left bottom row, and a
"paste"-combo for the index + middle finger on the left bottom row. Both combos are active on all layers.

#### Example 2: Home-row mods with positional hold-taps

Here we use ZMK's [positional
hold-tap](https://zmk.dev/docs/behaviors/hold-tap#positional-hold-tap-and-hold-trigger-key-positions)
feature to make home-row mods only trigger with "opposite hand" keys.[^1] Using our
positional shortcuts makes this straightforward: 

```C++
#define HRM_LT LM1 LM2 LM3 LM4                                      // left-hand HRMs
#define HRM_RT RM1 RM2 RM3 RM4                                      // right-hand HRMs
#define KEYS_LT LT0 LT1 LT2 LT3 LT4 LM0 HRM_LT LB0 LB1 LB2 LB3 LB4  // left-hand keys
#define KEYS_RT RT0 RT1 RT2 RT3 RT4 RM0 HRM_RT RB0 RB1 RB2 RB3 RB4  // right-hand keys
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                              // thumb keys

ZMK_BEHAVIOR(hml, hold_tap,  // left-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    global-quick-tap;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_RT THUMBS HRM_LT>;  // include left-hand HRMs for chording
)

ZMK_BEHAVIOR(hmr, hold_tap,  // right-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    global-quick-tap;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_LT THUMBS HRM_RT>;  // include right-hand HRMs for chording
)
```

[^1]: We also whitelist same-hand HRMs so that we can combine them to chord mods.
