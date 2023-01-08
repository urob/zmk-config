#!/usr/bin/env bash

ZMK_DIR="$HOME/zmk"
CONFIG_DIR="$HOME/zmk-config"
OUTPUT_DIR="$WINHOME/Downloads"
WEST_OPTS="$@"

# +-------------------------+
# | AUTOMATE CONFIG OPTIONS |
# +-------------------------+

cd "$CONFIG_DIR"

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

# usage: compile_board [board] [bin|uf2]
compile_board () {
    west build -d build/$1 -b $1 ${WEST_OPTS} -- -DZMK_CONFIG="$CONFIG_DIR/config" -Wno-dev
    if [[ $? -eq 0 ]]
    then
        OUTPUT="$OUTPUT_DIR/$1-zmk.$2"
        [[ -f $OUTPUT ]] && [[ ! -L $OUTPUT ]] && mv "$OUTPUT" "$OUTPUT".bak
        cp "$ZMK_DIR/app/build/$1/zephyr/zmk.$2" "$OUTPUT"
    fi
}

cd "$ZMK_DIR/app"
compile_board planck_rev6 bin
compile_board corneish_zen_v2_left uf2
compile_board corneish_zen_v2_right uf2
compile_board adv360pro_left uf2
compile_board adv360pro_right uf2

