#!/bin/bash
if [[ -d "/run/media/bernelius/XIAO-SENSE" ]]; then
    cp "./firmware/totem_left-seeeduino_xiao_ble.uf2" "/run/media/bernelius/XIAO-SENSE/"
    echo "cp command completed."
else
    echo "ERROR: No XIAO-SENSE found."
fi
