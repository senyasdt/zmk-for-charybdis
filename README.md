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
make build-senyatyl-dongle-debug
make build-senyatyl-left-debug
make build-senyatyl-right-peripheral-debug
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

For USB logs from the dongle, build or download the debug artifact:

```sh
make build-senyatyl-dongle-debug
```

Local output: `build/senyatyl_dongle_debug/zephyr/zmk.uf2`.
GitHub Actions artifact: `senyatyl_dongle_debug-seeeduino_xiao_ble-zmk`.

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

If Prospector shows `N/A` or red crosses for both halves, the dongle is not
connected to either split peripheral. Flash the debug dongle firmware, open its
USB serial log, then power-cycle both halves and look for:

- `Scanning successfully started`: dongle central is scanning for halves.
- `[DEVICE]`: dongle sees nearby BLE advertisements.
- `Found the split service`: an advertising half exposes the ZMK split service.
- `Connected`: the dongle connected to a split peripheral.
- `Unable to reserve peripheral slot` or `Create conn failed`: likely stale
  bonding or a central slot problem; repeat the full settings reset flow.

If the dongle sees BLE devices but never logs `Found the split service`, flash
the half debug artifacts one at a time and read their USB serial logs:

- `senyatyl_left_debug-nice_nano_v2-zmk`
- `senyatyl_right_peripheral_debug-nice_nano_v2-zmk`

The half logs should show BLE startup and split peripheral advertising. If a
half debug build does not expose a USB serial port, it is not the flashed
firmware currently running on that controller. The debug probe logs a heartbeat
like `Senyatyl split peripheral debug: connected=0 bonded=0` every two seconds.

## Senyatyl Layout

Visual layout tuning lives in a separate repository:

https://github.com/senyasdt/senyatyl-layout-editor

Use it to export both the ZMK `physical_layout_0.keys` block and `config/senyatyl.json` for Keymap Editor.
