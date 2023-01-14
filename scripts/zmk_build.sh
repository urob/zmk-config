#!/usr/bin/env bash

WEST_OPTS="$@"
OUTPUT_DIR="$WINHOME/Downloads"

HOST_ZMK_DIR="$HOME/zmk"
HOST_CONFIG_DIR="$HOME/zmk-config"

RUNWITH_DOCKER=true
DOCKER_SUDO="sudo"  # leave empty if user is in docker group
DOCKER_VERSION="zmkfirmware/zmk-dev-arm:3.0"

DOCKER_ZMK_DIR="/workspace/zmk"
DOCKER_CONFIG_DIR="/workspace/zmk-config"

# +-------------------------+
# | AUTOMATE CONFIG OPTIONS |
# +-------------------------+

cd "$HOST_CONFIG_DIR"

# update maximum combos per key
count=$( \
    tail -n +10 config/combos.dtsi | \
    grep -Eo '[LR][TMBH][0-9]' | \
    sort | uniq -c | sort -nr | \
    awk 'NR==1{print $1}' \
)
sed -Ei "/CONFIG_ZMK_COMBO_MAX_COMBOS_PER_KEY/s/=.+/=$count/" config/*.conf
echo "Setting MAX_COMBOS_PER_KEY to $count"

# update maximum keys per combo
count=$( \
    tail -n +10 config/combos.dtsi | \
    grep -o -n '[LR][TMBH][0-9]' | \
    cut -d : -f 1 | uniq -c | sort -nr | \
    awk 'NR==1{print $1}' \
)
sed -Ei "/CONFIG_ZMK_COMBO_MAX_KEYS_PER_COMBO/s/=.+/=$count/" config/*.conf
echo "Setting MAX_KEYS_PER_COMBO to $count"

# +--------------------+
# | BUILD THE FIRMWARE |
# +--------------------+

if [[ $RUNWITH_DOCKER = true ]]
then
    echo "Build mode: docker"
    DOCKER_CMD="$DOCKER_SUDO docker run --name zmk --rm -w $DOCKER_ZMK_DIR/app \
        --mount type=bind,source=$HOST_ZMK_DIR,target=$DOCKER_ZMK_DIR \
        --mount type=bind,source=$HOST_CONFIG_DIR,target=$DOCKER_CONFIG_DIR,readonly \
        --mount type=volume,source=zmk-root-user,target=/root \
        --mount type=volume,source=zmk-zephyr,target=$DOCKER_ZMK_DIR/zephyr \
        --mount type=volume,source=zmk-zephyr-modules,target=$DOCKER_ZMK_DIR/modules \
        --mount type=volume,source=zmk-zephyr-tools,target=$DOCKER_ZMK_DIR/tools \
        $DOCKER_VERSION"
    SUFFIX="_docker"
    CONFIG_DIR="$DOCKER_CONFIG_DIR/config"

else
    echo "Build mode: local"
    DOCKER_CMD=
    SUFFIX=
    CONFIG_DIR="$HOST_CONFIG_DIR/config"
fi

# usage: compile_board [board] [bin|uf2]
compile_board () {
    echo -e "\n$(tput setaf 4)Building $1$(tput sgr0)"
    $DOCKER_CMD west build -d "build/$1$SUFFIX" -b $1 $WEST_OPTS \
        -- -DZMK_CONFIG="$CONFIG_DIR" -Wno-dev
    if [[ $? -eq 0 ]]
    then
        echo "$(tput setaf 4)Success: $1 done$(tput sgr0)"
        OUTPUT="$OUTPUT_DIR/$1-zmk.$2"
        [[ -f $OUTPUT ]] && [[ ! -L $OUTPUT ]] && mv "$OUTPUT" "$OUTPUT.bak"
        cp "$HOST_ZMK_DIR/app/build/$1/zephyr/zmk.$2" "$OUTPUT"
    else
        echo "$(tput setaf 1)Error: $1 failed$(tput sgr0)"
    fi
}

cd "$HOST_ZMK_DIR/app"
compile_board planck_rev6 bin
compile_board corneish_zen_v2_left uf2
compile_board corneish_zen_v2_right uf2
compile_board adv360pro_left uf2
compile_board adv360pro_right uf2

