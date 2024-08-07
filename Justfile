default:
    @just --list --unsorted

build := ".build"
out := "firmware"

# build firmware
build board *args:
    #!/usr/bin/env bash
    set -euo pipefail
    BUILD="{{build}}/{{board}}"
    echo "Building firmware..."
    west build -d "$BUILD" -s zmk/app -b {{board}} {{args}} -- -DZMK_CONFIG="{{absolute_path('config')}}"
    if [[ -f "$BUILD/zephyr/zmk.uf2" ]]; then
        mkdir -p {{out}} && cp "$BUILD/zephyr/zmk.uf2" "{{out}}/{{board}}.uf2"
    else
        mkdir -p {{out}} && cp "$BUILD/zephyr/zmk.bin" "{{out}}/{{board}}.bin"
    fi

# clear build cache and artifacts
clean:
    rm -rf {{build}} {{out}}

# list all build targets
list:
    echo "TBD"

# initialize west
init:
    west init -l config
    west update
    west zephyr-export

# upgrade west
upgrade:
    west update

# upgrade zephyr
upgrade-zephyr:
    nix flake update --flake .
