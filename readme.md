# zmk-config

This is my personal [ZMK firmware](https://github.com/zmkfirmware/zmk/) configuration. 
It is ported from my QMK configuration, which in turn is heavily inspired by Manna Harbour's
[Miryoku layout](https://github.com/manna-harbour/miryoku).

## Key features

- clean keymap config + unicode support using
  [zmk-nodefree-config](https://github.com/urob/zmk-nodefree-config)
- home-row mods on base layer (with the [perfect configuration](#timeless-homerow-mods),
  sticky mods on `Nav` and `Num` layers
- most symbols can be accessed from the base layer via combos
- sticky shift on right thumb, double-tap activates caps-word
- backspace morphs into delete when shifted
- full numpad-layer with arithmetic operators (`=` via combo) and `Esc`, `Enter`, `Tab`
  on left hand (can be numlocked via `W + P` combo, ideal for data entry and
  right-handed mouse)
- "Greek" layer for mathematical typesetting

![](img/keymap.png)

## Timeless homerow mods

Homerow mods [are great](https://precondition.github.io/home-row-mods). But they can
require some finicky timings: In the most naive version, in order to produce a "mod"
they must be held longer than `tapping-term-ms`. While in order to produce a "tap", they
must be held less than `tapping-term-ms`. This requires very consistent typing speeds
that, alas, I do not possess. Hence my quest for a "timeless" HRM configuration. Here's
what I have ended up with.

Let's suppose for a moment we set `tapping-term-ms` to something ridiculously large, say
5 seconds. This makes the configuration "timeless". But obviously it creates two
undesired side-effects: (1) In order to get a "mod" we now have to hold the HRM keys for
something that feels eternity. (2) In normal typing, when tapping keys, there can be 
long delays between the press of a key and the time it appears on the screen.
Enter my two favorite configuration options:
* To alleviate the first side-effect, I use ZMK's `balanced` flavor, which will produce
  a "hold" if another key is both pressed and released within the tapping-term. Because
  that is exactly what I normally do with HRMs, there is virtually never a need to wait past my
  long tapping term (see below for two exceptions).
* To alleviate the typing delay, I use the `global-quick-tap` property, which will
  immediately resolve HRMs as "tap" when they are pressed
  shortly *after* another key has been tapped. This all but completely
  eliminates the delay when typing. 

This almost perfect, but there's still a few rough edges:

* While rolling keys quickly, I sometimes unintentionally end up with "nested" key
  sequences: `key 1` down, `key 2` down and up, `key 1` up. Given the `balanced` flavor,
  this would falsely register `key 1` as a mod. To prevent this, I use ZMK's "positional
  hold-tap" feature to force HRMs to always resolved as "tap" when the *next* key
  is on the same side of the keyboard. Problem solved.
* In the official ZMK version for positional hold-taps, the check whether the next key
  is on the same side of the keyboard is done upon *key press*. This is not
  ideal, because it prevents combining two modifiers on the same hand. To fix this, I
  use a small patch that delays the
  positional-hold-tap decision until *key release*. This way, multiple mods can be
  combined, while I still get the benefits of positional-hold-taps when tapping keys. 
  There is no PR yet (I am still in an
  early testing stage), but if you want to try, this is the [testing
  branch](https://github.com/urob/zmk/tree/positional-hold-tap-on-release).
* So far, nothing of the configuration depends on the duration of `tapping-term-ms`. In
  practice, there are two reasons why I don't set it to eternity:
    1. Sometimes, in rare circumstances, I want to combine a mod with a shortcut-key *on
       the same hand* (e.g., when the other hand uses a mouse). Our positional hold-tap
       configuration prevents this *within* the tapping term. By setting the tapping
       term to something large but not crazy large (I use 280ms), I can use same-hand
       `mod` + `shortcut` by by holding the mod just for a a while before pressing the
       shortcut-key.
    2. Sometimes, I want to press a modifier without another key (e.g., on Windows,
       tapping the `Win` key opens the search menu). Since the `balanced` flavour only
       kicks in when another key is pressed, this again requires waiting past
       `tapping-term-ms`.

Here's my configuration (I use a bunch of [helper
macros](https://github.com/urob/zmk-nodefree-config) to simplify the syntax, but they
are not necessary):

```
/* use helper macros to define left and right hand keys */
#include "../zmk-nodefree-config/keypos_def/keypos_36keys.h"                // keyposition helpers
#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left-hand keys
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right-hand keys
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumb keys

/* left-hand HRMs */
ZMK_BEHAVIOR(hml, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <175>;                // double tapping same key allows for repeating
    global-quick-tap-ms = <150>;         // without PR #1387 use global-quick-tap instead
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_R THUMBS>;
)

/* right-hand HRMs */
ZMK_BEHAVIOR(hmr, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <175>;                // double tapping same key allows for repeating
    global-quick-tap-ms = <150>;         // without PR #1387 use global-quick-tap instead
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_LT THUMBS>;  // include right-hand HRMs for chording
)
```
One last note, the configuration above uses some syntactic sugar introduced in [PR
#1387](https://github.com/zmkfirmware/zmk/pull/1387), which decouples the
`quick-tap-ms` timeout from the `global-quick-tap-ms` timeout. Without the PR, one
can replace `global-quick-tap-ms = <280>` with `global-quick-tap` for a
similar effect (`global-quick-tap` will use the regular `quick-tap-ms` timeout in this
case).

My personal [ZMK fork](https://github.com/urob/zmk) includes both the
global-quick-tap-ms PR as well as the positonal-hold-tap tweak (along with a few other
PRs).


## A few thoughts on the combo setup

The combo layout is guided by two goals: (1) put all combos in easy-to-access locations,
and (2) make them easy to remember. Specifically:

- the top vertical-combo row is almost equivalent to the symbols on standard number rows,
  making them easy to remember
- the bottom vertical-combo row is set up symmetrically to facilitate memorization
  (subscript `_` aligns with superscript `^`; minus `-` aligns with `+`; division `/`
  aligns with multiplication `*`; logical-or `|` aligns with logical-and `&`; backslash
  `\` aligns horizontally with forward slash `/`)
- parenthesis, braces and brackets in symmetric positions
- `!` and `?` are on home-row position for prime access
- a numlock shortcut (on `W + P`) for one-handed data entry
- shortcuts for cut (on `X + D`), copy, and paste on the left-hand side for right-handed
  mouse usage

