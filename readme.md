# mgkollander's fork of urob's zmk-config

NOTE: The description below is a very slight variation of urob's readme, edited for my own personal use. The keymap image is up to date.

This [ZMK firmware](https://github.com/zmkfirmware/zmk/)
configuration consists of a 42-keys base layout designed for the Corne.

## Highlights

- ["Timeless" homerow mods](#timeless-homerow-mods)
- Combos replace symbol layer
- Smart numbers and mouse layers auto-toggle off
- Unicode math and international leader key sequences
  [zmk-helpers](https://github.com/urob/zmk-helpers)
- Arrow-cluster doubles as <kbd>home</kbd>, <kbd>end</kbd>, <kbd>begin/end of
  document</kbd> on long-press
- More intuitive shift-actions: <kbd>, ;</kbd>, <kbd>. :</kbd> and <kbd>?
  !</kbd>
- QWERTY Gaming layer toggle

![](draw/keymap.png)

### Troubleshooting

- **Noticeable delay when tapping HRMs:** Increase `require-prior-idle-ms`. As a
  rule of thumb, you want to set it to at least `10500/x` where `x` is your
  (relaxed) WPM for English prose.[^3]
- **False negatives (same-hand):** Reduce `tapping-term-ms` (or disable
  `hold-trigger-key-positions`)
- **False negatives (cross-hand):** Reduce `require-prior-idle-ms` (or set
  flavor to `hold-preferred` -- to continue using `hold-trigger-on-release`, you
  must also
  [patch ZMK](https://github.com/celejewski/zmk/commit/d7a8482712d87963e59b74238667346221199293)
  or use [an already patched branch](https://github.com/urob/zmk))
- **False positives (same-hand):** Increase `tapping-term-ms`
- **False positives (cross-hand):** Increase `require-prior-idle-ms` (or set
  flavor to `tap-preferred`, which requires holding HRMs past tapping term to
  activate)

## Using combos instead of a symbol layer

- The top vertical-combo row matches the symbols on a standard numbers row
  (except `+` and `&` being swapped)
- The bottom vertical-combo row is symmetric to the top row (subscript `_`
  aligns with superscript `^`; minus `-` aligns with `+`; division `/` aligns
  with multiplication `*`; logical-or `|` aligns with logical-and `&`)
- Parenthesis, braces, brackets are set up symmetrically as horizontal combos
  with `<`, `>`, `{` and `}` being accessed from the Navigation layer (or when
  combined with `Shift`)
- Left-hand side combos for `tap`, `esc`, `enter`, `cut` (on <kbd>X</kbd> +
  <kbd>D</kbd>), `copy` and `paste` that go well with right-handed mouse usage
- <kbd>L</kbd> + <kbd>Y</kbd> switches to the Greek layer for a single key
  press, <kbd>L</kbd> + <kbd>U</kbd> + <kbd>Y</kbd> activates one-shot shift in
  addition
- <kbd>W</kbd> + <kbd>P</kbd> activates the smart mouse layer

## Smart layers and other gimmicks

##### Numword

Inspired by Jonas Hietala's
[Numword](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/#where-are-the-digits)
for QMK, I implemented my own
[Auto-layer behavior](https://github.com/urob/zmk-auto-layer) for ZMK to set up
Numword. It is triggered via a single tap on "Smart-Num". Numword continues to
be activated as long as I type numbers, and deactivates automatically on any
other keypress (holding it activates a non-sticky num layer).

After using Numword for more than a year now, I have been overall very happy
with it. When typing single digits, it effectively is a sticky-layer but with
the added advantage that I can also use it to type multiple digits.

The main downside is that if a sequence of numbers is _immediately_ followed by
any of the letters on which my numpad is located (WFPRSTXCD), then the automatic
deactivation won't work. But this is rare -- most number sequences are
terminated by `space`, `return` or some form of punctuation/delimination. To
deal with the rare cases where they aren't, there is a `CANCEL` key on the
navigation-layer that deactivates Numword, Capsword and Smart-mouse. (It also
toggles off when pressing `Numword` again, but I find it cognitively easier to
have a dedicated "off-switch" than keeping track of which modes are currently
active.)

##### Smart-Mouse

Similarly to Numword, I have a smart-mouse layer (activated by comboing
<kbd>W</kbd> + <kbd>P</kbd>), which replaces the navigation cluster with scroll
and mouse-movements, and replaces the right thumbs with mouse buttons. Pressing
any other key automatically deactivates the layer.

##### Capsword

My right thumb triggers three variations of shift: Tapping yields sticky-shift
(used to capitalize alphas), holding activates a regular shift, and
double-tapping (or equivalently shift + tap) activates ZMK's Caps-word behavior.

One minor technical detail: While it would be possible to implement the
double-tap functionality as a tap-dance, this would add a delay when using
single taps. To avoid the delays, I instead implemented the double-tap
functionality as a mod-morph.

##### Multi-purpose Navigation cluster

To economize on keys, I am using hold-taps on my navigation cluster, which yield
`home`, `end`, `begin/end of document`, and `delete word forward/backward` on
long-presses. The exact implementation is tweaked so that `Ctrl` is silently
absorbed in combination with `home` and `end` to avoid accidental document-wide
operations (which are accessible via the dedicated `begin/end document keys`.)

##### Swapper

I am using [Nick Conway](https://github.com/nickconway)'s fantastic
[tri-state](https://github.com/zmkfirmware/zmk/pull/1366) behavior for a
one-handed Alt-Tab switcher (`PWin` and `NWin`).

##### Leader key

I recently started using Nick Conway's
[Leader key](https://github.com/zmkfirmware/zmk/pull/1380) implementation for
ZMK. From my limited experience, I really like how it allows making less
commonly used behaviors accessible without binding them to a dedicated key. For
now I am using it for a variety of Unicode math symbols and international
characters. I am planning to extend the use to various firmware interactions
once I figure out the technical details.

## Issues and workarounds

Since I switched from QMK to ZMK I have been very impressed with how easy it is
to set up relatively complex layouts in ZMK. For the most parts I don't miss any
functionality (to the contrary, I found that ZMK supports many features natively
that would require complex user-space implementations in QMK). Below are a few
remaining issues:

- ZMK does not yet support "tap-only" combos
  ([#544](https://github.com/zmkfirmware/zmk/issues/544)), requiring a brief
  pause when wanting to chord HRMs that overlap with combo positions. As a
  workaround, I implemented all homerow combos as homerow-mod-combos. This is
  good enough for day-to-day, but does not address all edge cases (eg
  changing active mods).
- Very minor: `&bootloader` doesn't work with stm32 boards like the Planck
  ([#1086](https://github.com/zmkfirmware/zmk/issues/1086))

[^1]:
    I call it "timer-less", because the large tapping-term makes the behavior
    insensitive to the precise timings. One may say that there is still the
    `require-prior-idle` timeout. However, with both a large tapping-term and
    positional-hold-taps, the behavior is _not_ actually sensitive to the
    `require-prior-idle` timing: All it does is reduce the delay in typing;
    i.e., variations in typing speed won't affect _what_ is being typed but
    merely _how fast_ it appears on the screen.

[^2]:
    The delay is determined by how quickly a key is released and is not directly
    related to the tapping-term. But regardless of its length, most people still
    find it noticable and disruptive.

[^3]:
    E.g, if your WPM is 70 or larger, then the default of 150ms (=10500/70)
    should work well. The rule of thumb is based on an average character length
    of 4.7 for English words. Taking into account 1 extra tap for `space`, this
    yields a minimum `require-prior-idle-ms` of (60 _ 1000) / (5.7 _ x) ≈ 10500
    / x milliseconds. The approximation errs on the safe side, as in practice
    home row taps tend to be faster than average.
