#!/usr/bin/env bash

# TODO
# * add -c and -z argument to specity non-default branches for config and zmk
# * add option to pass arguments to west build (useful for -p)

ZMK_DIR="$HOME/zmk"
CONFIG_DIR="$HOME/zmk-config"
OUTPUT="$WINHOME/Downloads/planck_rev6-zmk.bin"

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

cd "$ZMK_DIR/app"

# build the firmware
west build -b planck_rev6 -- -DZMK_CONFIG="$CONFIG_DIR/config"

# copy firmware to Downloads if build was succesful
if [[ $? -eq 0 ]]
then
    [[ -f $OUTPUT ]] && [[ ! -L $OUTPUT ]] && mv "$OUTPUT" "$OUTPUT".bak
    cp "$ZMK_DIR/app/build/zephyr/zmk.bin" "$OUTPUT"
    exit 0
else
    exit 1
fi

