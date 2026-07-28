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

After flashing the dongle, pair the keyboard halves as peripherals. Pair the
left half first and the right half second so Prospector's peripheral battery
widgets are ordered left-to-right.

## Senyatyl Layout

Visual layout tuning lives in a separate repository:

https://github.com/senyasdt/senyatyl-layout-editor

Use it to export both the ZMK `physical_layout_0.keys` block and `config/senyatyl.json` for Keymap Editor.
