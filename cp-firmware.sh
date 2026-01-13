#!/usr/bin/env bash
uuid="0042-0042"  # replace with actual UUID shown by lsblk -f when in bootloader

device=$(blkid -U "$uuid" 2>/dev/null)
label=$(lsblk $device --output LABEL | tail -n 1)

destination="/run/media/$USER/$label"

rightlist=(
    "right"
    "r"
    "R"
    "Right"
)

echo "argument 1: $1"

for i in "${rightlist[@]}"; do
    if [[ $1 == $i ]]; then
        right=1
        break
    fi
done
if (( right )); then
    file="totem_right-seeeduino_xiao_ble.uf2"
else
    file="totem_left-seeeduino_xiao_ble.uf2"
fi

if [[ -b $device ]]; then
    udisksctl mount -b "$device" 2> /dev/null
    if [[ -d $destination ]]; then
        cp "$file" "$destination"
        sync
        echo "$file copied."
    else
        echo "ERROR: $destination is not a directory."
    fi
else
    echo "ERROR: device with UUID $uuid not found."
    echo "Cannot copy $file."
fi


