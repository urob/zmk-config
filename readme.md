# zmk-config

This is my personal [ZMK firmware](https://github.com/zmkfirmware/zmk/) configuration. 
It is ported from my QMK configuration, which in turn is heavily inspired by Manna Harbour's
[Miryoku layout](https://github.com/manna-harbour/miryoku).

## Key features

- clean keymap config + unicode support using
  [zmk-nodefree-config](https://github.com/urob/zmk-nodefree-config)
- home-row mods on base layer, sticky mods on `Nav` and `Num` layers
- most symbols can be accessed from the base layer via combos
- sticky shift on right thumb, double-tap activates caps-word
- backspace morphs into delete when shifted
- full numpad-layer with arithmetic operators (`=` via combo) and `Esc`, `Enter`, `Tab`
  on left hand (can be numlocked via `W + P` combo, ideal for data entry and
  right-handed mouse)
- "Greek" layer for mathematical typesetting

![](img/keymap.png)

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

