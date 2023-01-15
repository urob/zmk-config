#!/usr/bin/env bash

# Parse input arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        # needed when user isn't in docker group
        -s|--sudu)
            SUDO="sudo"
            ;;

        -v|--version)
            WEST_VERSION="$2"
            shift
            ;;

        --host-zmk-dir)
            HOST_ZMK_DIR="$2"
            shift
            ;;

        --docker-zmk-dir)
            DOCKER_ZMK_DIR="$2"
            shift
            ;;

        *)
            echo "Unknown option $1"
            exit 1
            ;;

    esac
    shift
done

# Set defaults
[[ -z $WEST_VERSION ]] && WEST_VERSION="3.0"
[[ -z $HOST_ZMK_DIR ]] && HOST_ZMK_DIR="$HOME/zmk"
[[ -z $DOCKER_ZMK_DIR ]] && DOCKER_ZMK_DIR="/workspace/zmk"

DOCKER_IMG="zmkfirmware/zmk-dev-arm:$WEST_VERSION"
DOCKER_CMD="$SUDO docker run --name zmk-$WEST_VERSION --rm \
    --mount type=bind,source=$HOST_ZMK_DIR,target=$DOCKER_ZMK_DIR \
    --mount type=volume,source=zmk-root-user-$WEST_VERSION,target=/root \
    --mount type=volume,source=zmk-zephyr-$WEST_VERSION,target=$DOCKER_ZMK_DIR/zephyr \
    --mount type=volume,source=zmk-zephyr-modules-$WEST_VERSION,target=$DOCKER_ZMK_DIR/modules \
    --mount type=volume,source=zmk-zephyr-tools-$WEST_VERSION,target=$DOCKER_ZMK_DIR/tools"

# Reset volumes
$SUDO docker volume rm $(sudo docker volume ls -q | grep "^zmk-.*-$WEST_VERSION$")

# Install west
$DOCKER_CMD -w "$DOCKER_ZMK_DIR" "$DOCKER_IMG" west init -l app/
$DOCKER_CMD -w "$DOCKER_ZMK_DIR" "$DOCKER_IMG" west update

# Install docosaurus
$DOCKER_CMD -w "$DOCKER_ZMK_DIR/docs" "$DOCKER_IMG" npm ci

