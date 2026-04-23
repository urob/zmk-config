# Changelog

## Summary

Updated ZMK configuration to be compatible with Zephyr 4.1.0 / ZMK v0.4.0 (post-v0.3.0) after rebasing onto upstream. This involved converting the custom eyelash_sofle board to a shield, updating the nice_view_gem display for LVGL 9.x compatibility, and fixing various board naming changes.

## Changes

### 1. Board Naming Updates

- **TOTEM**: Changed board from `seeeduino_xiao_ble` to `xiao_ble` (Zephyr 4.1.0 naming change)
  - Updated `build.yaml`
  - Updated `config/boards/shields/totem/totem.zmk.yml`
  - Updated `scripts/cp-firmware-totem`

### 2. Eyelash Sofle - Board to Shield Conversion

The eyelash_sofle was converted from a custom board to a shield on the `nice_nano` board:

**Removed:**
- `config/boards/arm/eyelash_sofle/` (entire custom board directory)

**Added:**
- `config/boards/shields/eyelash_sofle/`:
  - `Kconfig.defconfig` - Shield configuration with storage settings for BLE bonding
  - `Kconfig.shield` - Shield definitions
  - `eyelash_sofle.dtsi` - Device tree with GPIO mappings, RGB underglow, backlight, and reg0 (HV regulator) for radio stability
  - `eyelash_sofle_left.overlay` - Left half column GPIOs
  - `eyelash_sofle_right.overlay` - Right half column GPIOs
  - `eyelash_sofle.zmk.yml` - Shield metadata (updated to require nice_nano)
  - `eyelash_sofle.keymap` (moved from old board)
  - `eyelash_sofle-layouts.dtsi` (moved from old board)

**Updated:**
- `build.yaml`: Changed from board to shield with `nice_nano` as base board
- `config/eyelash_sofle.conf`: Added storage settings, removed experimental BLE features

### 3. Nice View Gem - LVGL 9.x Compatibility

**Removed local copy:**
- `config/boards/shields/nice_view_gem/` (local copy deleted)

**Forked and updated:**
- Created fork at `github.com:bernelius/nice-view-gem-z4`
- Updated for LVGL 9.x / Zephyr 4.1.0:
  - Changed `lv_img_dsc_t` to `lv_image_dsc_t`
  - Added `LV_IMAGE_HEADER_MAGIC` to image headers
  - Added stride calculation using `LV_DRAW_BUF_STRIDE`
  - Added `header.flags` and `header.reserved_2` fields
  - Changed `LV_IMG_DECLARE` to `LV_IMAGE_DECLARE`

**Updated:**
- `config/west.yml`: Point to forked nice-view-gem-z4 repository
- `build.yaml`: Use `nice_view_gem` shield

### 4. BLE and Storage Configuration

Added storage settings to `config/boards/shields/eyelash_sofle/Kconfig.defconfig`:
- `CONFIG_SETTINGS=y`
- `CONFIG_NVS=y`
- `CONFIG_FLASH=y`
- `CONFIG_FLASH_PAGE_LAYOUT=y`
- `CONFIG_FLASH_MAP=y`
- `CONFIG_USE_DT_CODE_PARTITION=y`

Added to `config/eyelash_sofle.conf`:
- `CONFIG_ZMK_BLE=y` (BLE enable)
- `CONFIG_BT_CTLR_TX_PWR_PLUS_8=y` (TX power)
- `CONFIG_CLOCK_CONTROL_NRF_K32SRC_XTAL=y` (32kHz crystal)
- `CONFIG_CLOCK_CONTROL_NRF_K32SRC_30PPM=y`

**Removed:**
- `CONFIG_ZMK_BLE_EXPERIMENTAL_FEATURES` (was causing PIN pairing issues)

### 5. Hardware Fixes

**Regulator Configuration:**
Added to `eyelash_sofle.dtsi`:
```dts
&reg0 {
    status = "okay";
};
```
This enables the high voltage DCDC regulator (reg0) for radio stability, matching the original custom board's `SOC_DCDC_NRF52X_HV` setting.

## Testing

- ✅ TOTEM builds and works correctly
- ✅ Eyelash Sofle builds successfully
- ✅ Nice View Gem display works with updated LVGL 9.x API
- ✅ Both halves pair correctly via BLE
- ✅ Key input works after pairing
- ✅ USB works when connected

## Breaking Changes

Users will need to:
1. Clear existing Bluetooth pairings from Windows/Mac
2. Flash settings_reset to clear old bonding keys
3. Re-pair the keyboard

## Related PRs/Commits

- Based on upstream ZMK commit: `0331b7d16e80954b807917f9323e59ffc1e3b626`
- Zephyr upgraded from 3.5.0 to 4.1.0
