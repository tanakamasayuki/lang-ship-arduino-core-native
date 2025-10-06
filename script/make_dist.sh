#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

choose_python() {
  if [[ -n "${PYTHON:-}" ]] && command -v "$PYTHON" >/dev/null 2>&1; then
    PYTHON_CMD=("$PYTHON")
    return
  fi
  if command -v python3 >/dev/null 2>&1; then
    PYTHON_CMD=(python3)
    return
  fi
  if command -v python >/dev/null 2>&1; then
    PYTHON_CMD=(python)
    return
  fi
  if command -v py >/dev/null 2>&1; then
    PYTHON_CMD=(py -3)
    return
  fi
  echo "Python 3 interpreter not found. Install Python 3 or set PYTHON env var." >&2
  exit 1
}

choose_python

TAG_OR_VERSION="${1:-}"

if [[ -n "$TAG_OR_VERSION" ]]; then
  VERSION_OUTPUT="$("${PYTHON_CMD[@]}" script/update_version.py --version "$TAG_OR_VERSION")"
else
  VERSION_OUTPUT="$("${PYTHON_CMD[@]}" script/update_version.py)"
fi

VERSION="$(echo "$VERSION_OUTPUT" | tail -n1)"

echo "Using version $VERSION"

DIST_DIR="$ROOT_DIR/dist"
PKG_NAME="lang-ship-native-$VERSION"
PKG_DIR="$DIST_DIR/$PKG_NAME"
ARCHIVE_PATH="$DIST_DIR/$PKG_NAME.zip"
SHA_PATH="$ARCHIVE_PATH.sha256"

rm -rf "$PKG_DIR"
mkdir -p "$PKG_DIR"

cp "$ROOT_DIR/platform.txt" "$PKG_DIR/"
cp "$ROOT_DIR/boards.txt" "$PKG_DIR/"
cp "$ROOT_DIR/LICENSE" "$PKG_DIR/"
cp "$ROOT_DIR/README.md" "$PKG_DIR/"
cp "$ROOT_DIR/README.ja.md" "$PKG_DIR/"

cp -R "$ROOT_DIR/cores" "$PKG_DIR/"
cp -R "$ROOT_DIR/variants" "$PKG_DIR/"

mkdir -p "$DIST_DIR"
rm -f "$ARCHIVE_PATH" "$SHA_PATH"

"${PYTHON_CMD[@]}" - "$PKG_DIR" "$ARCHIVE_PATH" <<'PY'
import pathlib
import sys
import zipfile

pkg_dir = pathlib.Path(sys.argv[1])
archive_path = pathlib.Path(sys.argv[2])
with zipfile.ZipFile(archive_path, 'w', zipfile.ZIP_DEFLATED) as zf:
    for path in pkg_dir.rglob('*'):
        relative = path.relative_to(pkg_dir.parent)
        zf.write(path, relative)
print(f"Created archive {archive_path}")
PY

"${PYTHON_CMD[@]}" - "$ARCHIVE_PATH" <<'PY'
import hashlib
import pathlib
import sys

archive = pathlib.Path(sys.argv[1])
sha_path = archive.with_suffix(archive.suffix + '.sha256')
sha = hashlib.sha256()
with archive.open('rb') as fh:
    for chunk in iter(lambda: fh.read(1024 * 1024), b''):
        sha.update(chunk)
sha_path.write_text(f"{sha.hexdigest()}  {archive.name}\n", encoding='utf-8')
print(f"SHA256: {sha.hexdigest()}")
PY

echo "Package ready: $ARCHIVE_PATH"
echo "Checksum: $(cat "$SHA_PATH")"

printf '%s\n' "$VERSION" > "$DIST_DIR/version.txt"
