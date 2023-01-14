#!/usr/bin/env bash

HOST_ZMK_DIR="$HOME/zmk"
DOCKER_ZMK_DIR="/workspace/zmk"

DOCKER_VERSION="zmkfirmware/zmk-dev-arm:3.0"

DOCKER_SUDO="sudo"  # leave empty if user is in docker group
DOCKER_CMD="$DOCKER_SUDO docker run --name zmk --rm \
    --mount type=bind,source=$HOST_ZMK_DIR,target=$DOCKER_ZMK_DIR \
    --mount type=volume,source=zmk-root-user,target=/root \
    --mount type=volume,source=zmk-zephyr,target=$DOCKER_ZMK_DIR/zephyr \
    --mount type=volume,source=zmk-zephyr-modules,target=$DOCKER_ZMK_DIR/modules \
    --mount type=volume,source=zmk-zephyr-tools,target=$DOCKER_ZMK_DIR/tools"

# Reset volumes
$DOCKER_SUDO docker volume rm $(sudo docker volume ls -q | grep zmk-)

# Install west
$DOCKER_CMD -w "$DOCKER_ZMK_DIR" "$DOCKER_VERSION" west init -l app/
$DOCKER_CMD -w "$DOCKER_ZMK_DIR" "$DOCKER_VERSION" west update

# Install docosaurus
$DOCKER_CMD -w "$DOCKER_ZMK_DIR/docs" "$DOCKER_VERSION" npm ci

