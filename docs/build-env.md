# Local build environment

The local build environment uses `nix`, `direnv` and `just` to set up a virtual development
environment with `west`, the `zephyr-sdk` and all their dependencies whenever you `cd` into the
workspace. The environment is _completely isolated_ and won't pollute your system.

Using it is entirely optional — see [Building the
firmware](../README.md#building-the-firmware) for the cloud-based alternative, which requires no
local setup at all.

## Prerequisites

1. Install the `nix` package manager:

   ```bash
   # Install Nix with flake support enabled
   curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix |
      sh -s -- install --no-confirm

   # Start the nix daemon without restarting the shell
   . /nix/var/nix/profiles/default/etc/profile.d/nix-daemon.sh
   ```

2. Install [`direnv`](https://direnv.net/) (and optionally but recommended
   [`nix-direnv`](https://github.com/nix-community/nix-direnv)[^1]) using your package manager of
   choice. E.g., using the `nix` package manager that we just installed[^2]:

   ```
   nix profile install nixpkgs#direnv nixpkgs#nix-direnv
   ```

3. Set up the `direnv` [shell-hook](https://direnv.net/docs/hook.html) for your shell. E.g., for
   `bash`:

   ```bash
   # Install the shell-hook
   echo 'eval "$(direnv hook bash)"' >> ~/.bashrc

   # Enable nix-direnv (if installed in the previous step)
   mkdir -p ~/.config/direnv
   echo 'source $HOME/.nix-profile/share/nix-direnv/direnvrc' >> ~/.config/direnv/direnvrc

   # Optional: make direnv less verbose
   echo '[global]\nwarn_timeout = "2m"\nhide_env_diff = true' >> ~/.config/direnv/direnv.toml

   # Source the bashrc to activate the hook (or start a new shell)
   source ~/.bashrc
   ```

   <details>
   <summary>Hooks for other shells</summary>

   Only the first line differs — the `nix-direnv` and verbosity settings above are shell-agnostic.

   ```bash
   # zsh
   echo 'eval "$(direnv hook zsh)"' >> ~/.zshrc

   # fish
   echo 'direnv hook fish | source' >> ~/.config/fish/config.fish
   ```

   See the [direnv documentation](https://direnv.net/docs/hook.html) for all supported shells.

   </details>

## Setting up the workspace

1. Fork this repository on GitHub, then clone *your fork*. I like to name my local clone
   `zmk-workspace` as it will be the toplevel of the development environment.

   ```bash
   # Replace `urob` with your username
   git clone https://github.com/urob/zmk-config zmk-workspace
   ```

2. Enter the workspace and set up the environment.

   ```bash
   # The first time you enter the workspace, you will be prompted to allow direnv
   cd zmk-workspace

   # Allow direnv for the workspace, which will set up the environment (this takes a while)
   direnv allow

   # Bootstrap the workspace from the manifest and pull in all dependencies
   # (same as `west init -l config && west update && west zephyr-export`)
   just init
   ```

## Usage

`just` is the entry point for all common tasks — running `just` without arguments lists all
available recipes.[^3]

### Building the firmware

To build the firmware, simply type `just build all` from anywhere in the workspace. This will parse
`build.yaml` and build the firmware for all board and shield combinations listed there. Compiled
firmware ends up in the `firmware` directory.

To only build the firmware for a specific target, use `just build <target>`. This will build the
firmware for all matching board and shield combinations. For instance, to build the firmware for my
Corneish Zen, I can type `just build zen`, which builds both `corneish_zen_v2_left` and
`corneish_zen_v2_right`. (`just list` shows all valid build targets.)

Additional arguments to `just build` are passed on to `west`. For instance, a pristine build can be
triggered with `just build all -p`. (Alternatively, `just clean` clears the build cache.)

### Flashing the firmware

For UF2-based boards, simply copy the compiled firmware from the `firmware` directory onto the
board's USB mass-storage device. For boards that don't support UF2 (like the Planck),
`just flash <target>` builds the firmware and flashes it via `west flash`.

### Drawing the keymap

The build environment packages [keymap-drawer](https://github.com/caksoylar/keymap-drawer).
`just draw` parses `base.keymap` and renders it to `draw/base.svg` (per-layer breakdown) and
`draw/overview.svg` (the condensed overview shown in the README).

### Devicetree formatter (experimental)

The build environment also packages a (patched and wrapped) version of
[`dts-linter`](https://github.com/kylebonnici/dts-linter). Usage:

```sh
dts-format [--fix] [--use-tabs] [--tab-width <int>] [filelist]
```

If no `filelist` is provided, `dts-format` will format all `dts`, `dtsi`, `overlay` and `keymap`
files _anywhere_ below the current working directory — Don't run this at the repo root unless you
want to format the entire zmk and zephyr base!

By default, `dts-format` will print a diff. Use the `--fix` flag to apply all changes directly to
the source files.

Use `--use-tabs` to indent lines with tabs (default is `spaces`) and use `--tab-width` to specify
the number of spaces per indentation level (default is `4`).

To protect manually aligned keymap blocks, guard them by `// dts-format off` and `// dts-format on`
comments.

### Hacking the firmware

To make changes to the ZMK source or any of the modules, simply edit the files or use `git` to pull
in changes. Because the workspace checks out each module as a regular git repository (under
`modules/zmk/`), the same environment doubles as a development environment for my [ZMK
modules](https://github.com/search?q=topic%3Azmk-module+fork%3Atrue+owner%3Aurob+&type=repositories).

To switch to any remote branches or tags, use `git fetch` inside a module directory to make the
remote refs locally available. Then switch to the desired branch with `git checkout <branch>` as
usual. You may also want to register additional remotes to work with or consider making them the
default in `config/west.yml`.

For module development, there is also a snapshot-test harness: `just test <path-to-test>` compiles
the keymap in the given test directory for ZMK's `native_sim` target, runs it, and diffs the
emitted keycode events against a stored snapshot. (Run with `--verbose` to see the events, or
`--auto-accept` to update the snapshot.) Note that these are tests for the _modules_, not for the
keymap in this repository — the keymap itself is validated by the cloud build.

### Updating the build environment

To sync ZMK and all modules to the revisions pinned in `config/west.yml`, run `just sync`. Make
sure to commit and push all local changes you have made to ZMK and the modules before running this
command, as it will overwrite them. To pull in _new_ upstream revisions, see [Pinning the
firmware](../README.md#pinning-the-firmware).

To upgrade the Zephyr SDK and Python build dependencies, use `just bump-nix`. (Use with care —
Running this will upgrade all Nix packages and may end up breaking the build environment. When in
doubt, I recommend keeping the environment pinned to `flake.lock`, which is [continuously
tested](https://github.com/urob/zmk-config/actions/workflows/test-build-env.yml) on Linux and
macOS.)

[^1]:
    `nix-direnv` provides a vastly improved caching experience compared to only having `direnv`,
    making entering and exiting the workspace instantaneous after the first time.

[^2]:
    This will permanently install the packages into your local profile, forgoing many of the
    benefits that make Nix uniquely powerful. A better approach, though beyond the scope of this
    document, is to use `home-manager` to maintain your user environment.

[^3]:
    Bonus tip: `just` provides
    [completion scripts](https://github.com/casey/just?tab=readme-ov-file#shell-completion-scripts)
    for many shells.
