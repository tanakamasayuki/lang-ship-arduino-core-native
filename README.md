# lang-ship Arduino Native SDL2 Platform

This repository hosts the `lang-ship:native` Arduino Boards Manager platform. It lets you execute M5Stack-compatible sketches on a desktop SDL2 environment so you can iterate quickly without flashing physical hardware.

## Features
- Mirrors the ESP32 M5Stack board definitions while targeting an SDL2 native runtime.
- Shares the same sketches between native and hardware builds with no code changes.
- Targets the M5Unified API used across M5Stack boards and depends on the M5GFX rendering engine; because M5GFX shares its core feature set with the author's LovyanGFX (different namespaces and supported panels), LovyanGFX sketches can be adapted by adjusting namespaces.
- Uses the system-provided SDL2, clang, and gcc toolchains (no bundled binaries yet).

## Prerequisites
- Arduino CLI or Arduino IDE (2.x recommended).
- SDL2 development libraries available on your system path.
- C/C++ toolchain accessible from the command line (clang/gcc).

## Getting Started
1. Clone this repository next to your Arduino CLI configuration or vendor index workspace.
2. Build a Boards Manager package once `platform.txt` and board definition files are in place (coming in the first release).
3. Install the package via Arduino CLI or Arduino IDE, then select the `lang-ship:native` target and upload as usual.

> **Tip:** If your toolchain binaries are installed in non-standard locations, you can override them with `sketch.yaml`:
>
> ```bash
> arduino-cli compile \
>   --fqbn lang-ship:native:m5stack_core \
>   --build-property compiler.path="C:/msys64/ucrt64/bin/"
> ```

## Version Management
- Tag releases with the semantic version (e.g. `v1.0.0`).
- Automation scripts will keep the `version=` field in `platform.txt` aligned with the latest tag.
- Running `script/make_dist.sh` also refreshes the version string before packaging.

## Roadmap
- Add the initial `platform.txt`, cores, and variant definitions for M5Stack boards.
- Provide helper scripts to validate builds and package indexes automatically.
- Bundle optional tools (SDL2, clang, gcc) for users without system-wide installations.

## Contributing
Issues and pull requests are welcome. Please ensure documentation remains in sync across `README.md` and `README.ja.md`.

## License
Released under the MIT License. See `LICENSE` for details.

