# Customization guide

Instructions for working on this ZMK config — written for coding agents, but equally usable by
humans adapting this repo as a starting point for their own keymap. For background on the keymap
and the build pipeline, see the [README](README.md).

## Ground rules

- **Building needs no local setup.** Pushing to a fork builds every target in `build.yaml` through
  GitHub Actions (`.github/workflows/build-nix.yml`, triggered by pushes and PRs touching
  `config/**` or `build.yaml`); the firmware is downloaded from the Actions tab. A fresh fork has
  Actions disabled — enable them once from the fork's Actions tab.
- **Building locally** requires the nix-based dev environment (nix + direnv, see the
  [README](README.md#local-build-environment)) plus a one-time `just init`, which turns the
  repository into a west workspace by pulling in ZMK, Zephyr and the modules. Then verify keymap
  changes with `just build <target>` (`just list` shows valid targets, `just build all` builds
  everything); compiled firmware lands in `firmware/`. If `just` or `west` are missing, the
  environment isn't active — run commands through `nix develop --command <cmd>` or activate with
  `direnv allow`.
- `config/west.yml` is maintained by [pin-west](https://github.com/urob/pin-west): never hand-edit
  pinned revisions, run `pin-west bump` instead. Adding or removing a module is fine — edit the
  entry itself and re-run `pin-west pin` to (re)pin.
- `dts-format` (packaged in the dev environment) formats devicetree files. It does not reformat
  C-preprocessor macros, so on the keymaps it is close to a no-op — the hand-aligned grids inside
  `ZMK_LAYER` are safe and need no guarding. It earns its keep on plain devicetree, i.e. when
  developing modules or board definitions. Without arguments it recurses over the working
  directory; pass files explicitly to narrow it.
- After keymap changes that affect the layout, regenerate the diagrams with `just draw` (renders
  `draw/base.svg` and `draw/overview.svg` from the 34-key base keymap).
- `just test` is a snapshot-test harness for developing the ZMK **modules** checked out under
  `modules/zmk/`. It does not test this repo's keymap; the keymap is validated by building.

## How the multi-board layout works

`config/base.keymap` defines all layers exactly once, for 34 keys, using the standardized key labels
from [zmk-helpers](https://github.com/urob/zmk-helpers): `LT0`–`LT4`, `LM0`–`LM4`, `LB0`–`LB4` and
`LH0`–`LH2` for the left top/middle/bottom rows and thumbs, mirrored with `R` on the right (`0` is
innermost). HRM trigger positions, combos (`config/combos.dtsi`), the leader key and the mouse layer
are all written against these labels — so they adapt to any board automatically.

`base.keymap` intentionally includes **no** key-labels header itself. Each board has a small entry
keymap that must, in this order:

1. optionally `#define CONFIG_WIRELESS` (enables the Bluetooth keys on the Sys layer),
2. define a `ZMK_BASE_LAYER(name, LT, RT, LM, RM, LB, RB, LH, RH)` macro that places the eight
   34-key blocks onto the board's full physical grid, filling leftover keys with `&none` or extra
   bindings,
3. include the matching key-labels header from zmk-helpers,
4. `#include "base.keymap"`.

`config/corneish_zen.keymap` is a minimal reference example; `config/planck_rev6.keymap` shows a
non-split, wired board; `config/glove80.keymap` shows a much larger board.

## Adding a new board

1. **Decide on the structure first.** The modular layout above only pays off across several
   boards. If the new board is the only one you build for, consider dropping the indirection:
   widen `base.keymap` to the board's full key count (turn the `ZMK_BASE_LAYER` calls into plain
   `ZMK_LAYER` calls spanning every physical key), add the key-labels `#include` at its top, and
   rename it to `<board>.keymap` so it becomes the entry point. Combos, HRM trigger positions and
   the mouse layer keep working as long as the key labels do. (For a true 34-key board, no adapter
   is needed either way — `base.keymap` has a pass-through fallback.) The steps below assume the
   modular layout.

2. **Identify the ZMK board/shield names** for the hardware (e.g. `nice_nano_v2` +
   `corne_left`/`corne_right`), from the ZMK docs or the board's vendor config.

3. **Check for an existing key-position header** in
   `modules/zmk/helpers/include/zmk-helpers/key-labels/` (after `just init`; the same list is in
   the [zmk-helpers repo](https://github.com/urob/zmk-helpers/tree/main/include/zmk-helpers/key-labels)).
   Many layouts already have one, either by name (`glove80.h`, `sofle.h`, …) or by shape (`36.h`,
   `42.h`, `4x12_wide.h`, …).

   If none matches, write the key-position defines yourself — either at the top of the new entry
   keymap or, better, as a new header contributed to zmk-helpers — following the naming and
   mirroring conventions documented in
   [key_labels.md](https://github.com/urob/zmk-helpers/blob/main/docs/key_labels.md#standardization).

4. **Create `config/<board>.keymap`** following the four-step structure above. Start from
   `corneish_zen.keymap` for wireless splits or `planck_rev6.keymap` for wired boards. When
   mapping the blocks in `ZMK_BASE_LAYER`, keep the 34 base positions in their standard relative
   locations and spend spare physical keys on duplicates or extras (the existing adapters use
   `&kp LGUI` and `&smart_mouse`).

5. **Create `config/<board>.conf`**, copying from an existing one: wireless boards want the sleep
   and Bluetooth settings from `corneish_zen.conf`; all boards want `CONFIG_ZMK_POINTING=y` for
   the mouse layer.

6. **Register the build target** in `build.yaml` under `include:`, as `board:` (plus `shield:` for
   shield-based hardware). Board revisions use ZMK's `name@rev//zmk` syntax — see the existing
   entries.

7. **Build and check**: `just build <name>` (any substring of the board/shield matches), then
   confirm the artifact appears in `firmware/`.

## Where to change what

| Change                            | File                                                              |
| --------------------------------- | ----------------------------------------------------------------- |
| Layers, HRMs, thumb keys          | `config/base.keymap`                                              |
| HRM timing                        | `config/base.keymap` (`tapping-term-ms`, `require-prior-idle-ms`; see README troubleshooting) |
| Combos                            | `config/combos.dtsi` (position diagram at the top)                |
| Leader sequences                  | `config/leader.dtsi`                                              |
| Mouse layer                       | `config/mouse.dtsi`                                               |
| Per-board keys, physical mapping  | `config/<board>.keymap`                                           |
| Board settings (BT, sleep, mouse) | `config/<board>.conf`                                             |
| Build targets                     | `build.yaml`                                                      |
| ZMK/module versions               | `config/west.yml` (via `pin-west bump` only)                      |
| Dev environment                   | `flake.nix`, `nix/` (test with `nix develop`)                     |

Removing a feature: delete its `#include` from `base.keymap` (and its bindings/combo references),
and if it was the only consumer of a module, drop the module's entry from `config/west.yml`. The
modules used per feature are commented at the top of `base.keymap`.
