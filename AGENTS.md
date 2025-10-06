# AGENTS

## Mission
- Deliver an Arduino Boards Manager platform that runs M5Stack sketches on a native SDL2 backend.
- Mirror the behavior of the official ESP32 M5Stack boards so sketches can be tested locally without hardware.

## Key Repository Facts
- Vendor ID: `lang-ship`; Architecture: `native`.
- License: MIT.
- SDL2, clang, and gcc are expected to be available on the host system for now.
- Future releases may bundle additional tooling under `tools/`.

## Responsibilities
- Keep scripts updating `platform.txt`'s `version=` in sync with Git tags.
- Ensure `script/make_dist.sh` refreshes the version string based on the latest tag.
- Provide overrides via `sketch.yaml` build properties when local toolchains live in non-standard paths.

## Workflow Guardrails
- Prefer automated checks and lightweight scripts before publishing to the Arduino index.
- Avoid touching user-managed configuration or system-wide toolchains; document manual steps instead.
- When in doubt, document assumptions in `README.md` (and sync with `README.ja.md`).

## Communication
- Keep documentation and code comments in English.
- README is English-first, with `README.ja.md` offering a Japanese translation maintained alongside.

