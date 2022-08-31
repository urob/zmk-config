# urob's zmk-config

This is my personal [ZMK firmware](https://github.com/zmkfirmware/zmk/) configuration. 
It is ported from my QMK configuration, which in turn is heavily inspired by Manna Harbour's
[Miryoku layout](https://github.com/manna-harbour/miryoku).

## Key features

- clean keymap + unicode setup using helper macros from
  [zmk-nodefree-config](https://github.com/urob/zmk-nodefree-config)
- keymap and combo setup portable across different physical layouts
- ["timeless" homerow mods](#timeless-homerow-mods) on the base layer;
  sticky mods on other layers
- combos replacing the symbol layer
- sticky shift on right thumb, double-tap activates caps-word
- shift + space morphs into dot + space + sticky-shift
- shift + backspace morphs into delete
- "Greek" layer for mathematical typesetting

![](img/keymap.png)

## Timeless homerow mods

Homerow mods [are great](https://precondition.github.io/home-row-mods). But they can
require some finicky timing: In its most naive implementation, in order to produce a "mod",
they must be held *longer* than `tapping-term-ms`. In order to produce
a "tap", they must be held *less* than `tapping-term-ms`. This requires very consistent
typing speeds that, alas, I do not possess. Hence my quest for a "timeless" HRM
setup.[^1]

Here's what I have ended up with: A "timeless" HRM setup with virtually no misfires and
yet a fluent typing experience with mostly no delays.

Let's suppose for a moment we set `tapping-term-ms` to something ridiculously large, say
5 seconds. This makes the configuration "timeless". But it also creates two
problems: (1) In order to get a "mod" we now have to hold the HRM keys for
what feels like eternity. (2) In normal typing, when tapping keys, there can be
long delays between the press of a key and the time it appears on the screen. Enter my
two favorite configuration options:
* To address the first problem, I use ZMK's `balanced` flavor, which produces
  a "hold" if another key is both pressed and released within the tapping-term. Because
  that is exactly what I normally do with HRMs, there is virtually never a need to wait
  past my long tapping term (see below for two exceptions).
* To address the typing delay, I use ZMK's `global-quick-tap` property, which
  immediately resolves a HRM as "tap" when it is pressed shortly *after* another key
  has been tapped.[^2] This all but completely eliminates the delay when typing. 

This is almost perfect, but there's still a few rough edges:

* When rolling keys, I sometimes unintentionally end up with "nested" key
  sequences: `key 1` down, `key 2` down and up, `key 1` up. Given the `balanced` flavor,
  this would falsely register `key 1` as a mod. To prevent this, I use ZMK's "positional
  hold-tap" feature to force HRMs to always resolve as "tap" when the *next* key is on
  the same side of the keyboard. Problem solved.
* ... or at least almost. The official ZMK version for positional-hold-taps performs the
  positional check when the next key is *pressed*. This is not ideal, because it
  prevents combining multiple modifiers on the same hand. To fix this, I use a small
  patch that delays the positional-hold-tap decision until the next key's *release* ([PR
  #1423](https://github.com/zmkfirmware/zmk/pull/1423)). With the patch, multiple mods
  can be combined when held, while I still get the benefit from positional-hold-taps
  when keys are tapped.
* So far, nothing of the configuration depends on the duration of `tapping-term-ms`. In
  practice, there are two reasons why I don't set it to infinity:
    1. Sometimes, in rare circumstances, I want to combine a mod with a alpha-key *on
       the same hand* (e.g., when using the mouse with the other hand). My positional
       hold-tap configuration prevents this *within* the tapping term. By setting the
       tapping term to something large but not crazy large (I use 280ms), I can still
       use same-hand `mod` + `alpha` shortcuts by holding the mod for just a little while
       before tapping the alpha-key.
    2. Sometimes, I want to press a modifier without another key (e.g., on Windows,
       tapping `Win` opens the search menu). Because the `balanced` flavour only
       kicks in when another key is pressed, this also requires waiting past
       `tapping-term-ms`.

Here's my configuration (I use a bunch of [helper
macros](https://github.com/urob/zmk-nodefree-config) to simplify the syntax, but they
are not necessary):

```C++
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
    hold-trigger-on-release;             // requires PR #1423
)

/* right-hand HRMs */
ZMK_BEHAVIOR(hmr, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <175>;                // double tapping same key allows for repeating
    global-quick-tap-ms = <150>;         // without PR #1387 use global-quick-tap instead
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_L THUMBS>;
    hold-trigger-on-release;             // requires PR #1423
)
```
One last note, the configuration above uses some syntactic sugar introduced in [PR
#1387](https://github.com/zmkfirmware/zmk/pull/1387), which decouples the
`quick-tap-ms` timeout from the `global-quick-tap-ms` timeout. Without the PR, one
can replace `global-quick-tap-ms = <150>` with `global-quick-tap` for a
similar effect (`global-quick-tap` will use the regular `quick-tap-ms` timeout in this
case).

My personal [ZMK fork](https://github.com/urob/zmk) includes both the
global-quick-tap-ms PR and the hold-trigger-on-release PR (along with a few other PRs).
If you are looking for a ZMK-centric introduction to maintaining your own fork with a
custom selection of PRs, you might find my ["cookbook
approach"](https://gist.github.com/urob/68a1e206b2356a01b876ed02d3f542c7) helpful.


## A few thoughts on the combo setup

The combo layout is guided by two goals: (1) put all combos in easy-to-access locations,
and (2) make them easy to remember. Specifically:

- the top vertical-combo row matches the symbols on a standard numbers row
  (except `+` and `&` being swapped)
- the bottom vertical-combo row aims for symmetry with the top row
  (subscript `_` aligns with superscript `^`; minus `-` aligns with `+`; division `/`
  aligns with multiplication `*`; logical-or `|` aligns with logical-and `&`)
- parenthesis, braces, brackets, `!` and `?` all in prime access locations and set up
  symmetrically
- a numlock shortcut (on `W + P`) for one-handed "data entry" (aka Sudoku 🙂)
- shortcuts for cut (on `X + D`), copy, and paste on left side (good with right-handed
  mouse use)

[^1]: I call it "timeless", because the large tapping-term makes the behavior
  insensitive to the precise timings. One may say that there is still the
  `global-quick-tap` timeout. However, with both a large tapping-term and
  positional-hold-taps, the behavior is *not* actually sensitive to the
  `global-quick-tap` timing: All it does is reduce the delay in typing; i.e., variations
  in typing speed won't affect *what* is being typed but merly *how fast* it appears on
  the screen.

[^2]: One potential downside of `global-quick-tap` is that it prevents using modifiers
  *immediately* after another key press. Arguably, this is only problematic for shift,
  which is not a problem for me, because I have a dedicated "sticky shift" on my right
  thumb. If you rely on homerow mods for regular capitalization, you may want to reduce
  the `global-quick-tap` term for just the two shift-mods to about 75-100ms.
