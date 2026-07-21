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
make build-reset
make build-eyelash-corne-left
make build-eyelash-corne-right
make shell
make clean
```

Firmware artifacts are written under `build/*/zephyr/`.

## Senyatyl Layout

Visual layout tuning lives in a separate repository:

https://github.com/senyasdt/senyatyl-layout-editor

Use it to export both the ZMK `physical_layout_0.keys` block and `config/senyatyl.json` for Keymap Editor.

## Eyelash Corne

The Eyelash Corne keyboard lives alongside the other keyboards in this repo:

- board files: `config/boards/arm/eyelash_corne/`
- keymap/config/json: `config/eyelash_corne.*`
- GitHub Actions matrix: `builds/eyelash_corne.yaml`
- workflow artifacts: `eyelash-corne-firmware`
