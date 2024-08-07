default:
    @just --list --unsorted

# build firmware
build:
    echo "Building firmware..."

# clear build cache
clean:
    rm -rf build

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
