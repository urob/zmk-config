#!/bin/bash
if [[ -d "/Volumes/XIAO-SENSE" ]]; then
    cp "./firmware/totem_left-seeeduino_xiao_ble.uf2" "/Volumes/XIAO-SENSE/"
else
    echo "ERROR: No XIAO-SENSE found."
fi
