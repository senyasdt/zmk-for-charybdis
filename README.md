zmk-config for charybdis (3x6)

## Local build

Build with Docker:

```sh
make build-all
```

Useful targets:

```sh
make build-left
make build-right
make build-dongle
make build-senyatyl-dongle
make build-senyatyl-all
make build-reset
make build-reset-xiao
make shell
make clean
```

Firmware artifacts are written under `build/*/zephyr/`.

## Prospector

Charybdis and Senyatyl use the `prospector-zmk-module` module from
`config/west.yml`. Prospector firmware is built as a dongle-central image for a
Seeed XIAO BLE with the keyboard dongle shield plus `prospector_adapter`:

```yaml
shield: charybdis_dongle prospector_adapter
shield: senyatyl_dongle prospector_adapter
```

For Senyatyl, build locally with:

```sh
make build-senyatyl-dongle
```

The Senyatyl dongle is configured for two BLE split peripherals. Flash the
halves with `senyatyl_left` and `senyatyl_right_peripheral`; do not use the
regular `senyatyl_right` firmware with the dongle, because that build is a
right-half central.

When switching an existing keyboard from right-half central to dongle central,
reset BLE settings on all controllers first:

1. Flash `settings_reset-nice_nano_v2-zmk` to the left half.
2. Flash `settings_reset-nice_nano_v2-zmk` to the right half.
3. Flash `settings_reset-seeeduino_xiao_ble-zmk` to the Prospector dongle.
4. Remove the old keyboard pairing from the host OS.
5. Flash `senyatyl_left`, `senyatyl_right_peripheral`, and
   `senyatyl_dongle-seeeduino_xiao_ble-zmk`.
6. Pair the left half first and the right half second so Prospector's peripheral
   battery widgets are ordered left-to-right.

## Senyatyl Layout

Visual layout tuning lives in a separate repository:

https://github.com/senyasdt/senyatyl-layout-editor

Use it to export both the ZMK `physical_layout_0.keys` block and `config/senyatyl.json` for Keymap Editor.
