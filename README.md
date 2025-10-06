# lang-ship Arduino Native SDL2 Platform

This repository hosts the `lang-ship:native` Arduino Boards Manager platform. It lets you execute M5Stack-compatible sketches on a desktop SDL2 environment so you can iterate quickly without flashing physical hardware.

## Features
- Mirrors the ESP32 M5Stack board definitions while targeting an SDL2 native runtime.
- Shares the same sketches between native and hardware builds with no code changes.
- Targets the M5Unified API used across M5Stack boards and depends on the M5GFX rendering engine; because M5GFX shares its core feature set with the author's LovyanGFX (different namespaces and supported panels), LovyanGFX sketches can be adapted by adjusting namespaces.
- Uses the system-provided SDL2, clang, and gcc toolchains (no bundled binaries yet).
- Provides an initial `m5stack_core` board profile with a placeholder pin map and SDL2-powered main loop stub.

## Getting Started
1. Clone this repository into your Arduino hardware directory (for example `~/Arduino/hardware/lang-ship/native`).
2. Compile a sketch with Arduino CLI:
   ```bash
   arduino-cli compile \
     --fqbn lang-ship:native:m5stack_core \
     path/to/your/sketch
   ```
3. Run the generated executable from the build folder (on Windows the default artifact ends with `.exe`).
4. Override toolchain discovery when required:
   ```bash
   arduino-cli compile \
     --fqbn lang-ship:native:m5stack_core \
     --build-property compiler.path="C:/msys64/ucrt64/bin/" \
     --build-property build.exec_ext=.exe \
     path/to/your/sketch
   ```

## Directory Layout
- `platform.txt`: compiler configuration, SDL2 link flags, and build recipes.
- `boards.txt`: registers the `m5stack_core` SDL2 target with default build flags.
- `cores/native`: prototype Arduino core providing timing, Serial output, and the SDL2 event loop entry point.
- `variants/m5stack_core`: placeholder pin assignments and variant hook for the M5Stack profile.

## Toolchain Overrides
- `compiler.path` defaults to an empty string so the system `PATH` is used; supply a custom directory with `--build-property compiler.path=...`.
- `build.exec_ext` controls the executable suffix (defaults to `.exe` in `boards.txt`). Override it when targeting POSIX environments.
- Append extra SDL2 linker flags with `--build-property build.sdl_ldflags="-lSDL2main"` if your local setup requires them.

## Version Management
- Tag releases with the semantic version (e.g. `v1.0.0`).
- Automation scripts will keep the `version=` field in `platform.txt` aligned with the latest tag.
- Running `script/make_dist.sh` also refreshes the version string before packaging.

## Current Limitations
- Peripheral emulation is minimal—GPIO, audio, and graphics hooks are placeholders awaiting SDL2-based drivers.
- Serial input is synchronous and line-buffered via `std::cin`; non-blocking behaviour is not implemented yet.
- `arduino-cli upload` is not wired; run the built executable manually for now.

## Roadmap
- Flesh out the `cores/native` implementation to drive M5Unified and LovyanGFX on SDL2.
- Provide helper scripts to validate builds and package indexes automatically.
- Bundle optional tools (SDL2, clang, gcc) for users without system-wide installations.

## Contributing
Issues and pull requests are welcome. Please ensure documentation remains in sync across `README.md` and `README.ja.md`.

## License
Released under the MIT License. See `LICENSE` for details.



