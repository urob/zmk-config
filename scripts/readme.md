This folder contains scripts that automate installing and building using a local
toolchain. The scripts provide an alternative to using
[Github Actions](https://zmk.dev/docs/user-setup#installing-the-firmware) and
the [developer toolchain](https://zmk.dev/docs/development/setup).

If the zmk-config repo contains a `combos.dtsi` file, the script will also
automatically update the `MAX_COMBOS_PER_KEY` and `MAX_KEYS_PER_COMBO` settings
for all boards, depending on the combos specified in `combos.dtsi`.

If the `west.yml` contains any modules other than `ZMK`, the script will look for them in
`HOST_MODULES_DIR` and automatically enable them for the build.

## Build steps

### 1. Clone the ZMK repository

Clone the ZMK repository and checkout the branch that you want to build against.
By default the build script will look for the ZMK repo in `~/zmk`. Other
locations can be specified with `--host-zmk-dir` or by changing the default
location for `HOST_ZMK_DIR` inside the script.

For example, to build against my `main-3.2` branch, run:

```bash
cd "$HOME"
git clone https://github.com/urob/zmk
git checkout main-3.2
```

### 2. Clone your zmk-config repository

By default the build script will look for the zmk-config repo in `~/zmk-config`.
Other locations can be specified with `--host-config-dir` or by changing the
default location for `HOST_CONFIG_DIR` inside the script.

For example, to use my zmk-config repo, run:

```bash
cd "$HOME"
git clone https://github.com/urob/zmk-config
```

### 3. Install the build requisites

The build script can be used to install either a "docker" or a "local"
toolchain. If unsure, I recommend using the docker toolchain. Depending on your
installation choice, do **one** of the following:

1. Install `yq` and `Docker` or `Podman` (recommended). If using Podman, configure the
   docker registry. On Debian or Ubuntu, you can do both by running:
   ```bash
   sudo apt-get install podman yq
   echo 'unqualified-search-registries = ["docker.io"]' > $XDG_CONFIG_HOME/containers/registries.conf
   ```
2. Install a local
   [developer toolchain](https://zmk.dev/docs/development/setup). The
   `zmk_local_install.sh` script in this repository automates the process for
   Debian-based operating system.

### 4. Run the build script

Run the `zmk_build.sh` script to build your boards. By default, the script will
build all boards specified in `build.yaml` in your `zmk-config` repo. The
default can be overwritten with the `-b` option.

If using docker/podman, the script will pull down the required dependencies the
first time it is used. The script will automatically detect whether the build
requirement have changed, and will only re-download the dependencies if needed.

In order to easily switch between multiple ZMK branches that have different
build requirements, one can specify the desired Zephyr version using the `-v`
option. Docker container and volumes are index by the Zephyr version, so
switching between Zephyr version won't require re-downloading new dependencies.
In order to force re-installing all build requirements, pass the `-c` option,
which will wipe out the Docker container and volume.

By default the script will copy the firmware into the `OUTPUT_DIR` folder
specified in the script. Other locations can be specified using the
`--output-dir` argument.

To switch between Docker and Podman, set the `DOCKER_BIN` variable in the script
(defaults to `podman`). If using Docker and the user is not in the docker-group,
then one can use Docker in sudo-mode by using the `-s` flag for the script. If
using Podman, running in rootless mode is recommended.

One can pass custom options to `west` by preluding them with `--`.

For example, to build my boards using Zephyr version 3.2 in sudo mode and pass
the "pristine" option to west, run:

```bash
zmk_build.sh -s -v 3.2 -- -p
```

See the script for a full set of options.

## Developing interactively using Docker

The docker container can be entered interactively using with all the necessary
mounts using: The script shares a build environment with the build script (again
indexed by Zephyr versions).

For example, to start an interactive Docker session in sudo mode using Zephyr
version 3.2, run:

```bash
zmk_run_docker.sh -s -v 3.2
```
