# pen

Clock plugin for dictionary-pen style Qt/QML devices.

## Build target

- Output: `libclock_plugin.so`
- Primary target: Linux ARM64 (`aarch64`)
- Runtime module: `MyPlugins.Clock 1.0`

## CI build (GitHub Actions)

This repository includes an ARM64 cross-build workflow:

- Workflow file: `.github/workflows/build-clock-plugin.yml`
- Runner: `archlinux:latest` container on GitHub Actions
- Toolchain: `aarch64-linux-gnu-gcc 6.5.0` (glibc 2.27)
- Qt SDK: prebuilt `aarch64-linux-qt-5.15.2`

After each push (or manual run), download the `.so` from **Actions > Artifacts**.
