#!/usr/bin/env python3
"""Synchronize platform.txt version with the latest tag or supplied version.

Usage examples:
  python script/update_version.py            # use latest annotated tag
  python script/update_version.py --version v1.2.3
  python script/update_version.py --dry-run

The script prints the normalized semantic version (without a leading "v") to stdout.
"""
from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys
from typing import Optional

RE_VERSION = re.compile(r"^[0-9]+(\.[0-9]+)*([0-9A-Za-z._-]*)?$")

def git_latest_tag() -> str:
    try:
        result = subprocess.run(
            ["git", "describe", "--tags", "--abbrev=0"],
            check=True,
            capture_output=True,
            text=True,
        )
    except subprocess.CalledProcessError as exc:
        raise SystemExit("Failed to resolve latest git tag. Specify --version explicitly.") from exc
    tag = result.stdout.strip()
    if not tag:
        raise SystemExit("No git tags found. Specify --version explicitly.")
    return tag

def normalize_version(tag_or_version: str) -> str:
    candidate = tag_or_version.strip()
    if candidate.startswith("refs/tags/"):
        candidate = candidate[len("refs/tags/"):]
    if candidate.lower().startswith("v") and len(candidate) > 1 and candidate[1].isdigit():
        candidate = candidate[1:]
    if not RE_VERSION.match(candidate):
        raise SystemExit(f"Unsupported version format: {tag_or_version}")
    return candidate

def update_platform_version(platform_path: pathlib.Path, version: str, write: bool) -> bool:
    content = platform_path.read_text(encoding="utf-8")
    new_content, count = re.subn(r"(?m)^version\s*=.*$", f"version={version}", content)
    if count == 0:
        raise SystemExit(f"Could not find version field inside {platform_path}")
    if write and new_content != content:
        platform_path.write_text(new_content, encoding="utf-8")
        return True
    return False

def parse_args(argv: Optional[list[str]] = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Update platform.txt version field")
    parser.add_argument(
        "--version",
        help="Version or tag to apply. If omitted, uses latest git tag.",
    )
    parser.add_argument(
        "--platform",
        default=str(pathlib.Path(__file__).resolve().parents[1] / "platform.txt"),
        help="Path to platform.txt (default: repository root/platform.txt)",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Show the resulting version without writing platform.txt",
    )
    return parser.parse_args(argv)

def main(argv: Optional[list[str]] = None) -> int:
    args = parse_args(argv)
    tag = args.version or git_latest_tag()
    version = normalize_version(tag)

    platform_path = pathlib.Path(args.platform).resolve()
    if not platform_path.exists():
        raise SystemExit(f"platform.txt not found at {platform_path}")

    changed = update_platform_version(platform_path, version, write=not args.dry_run)
    if args.dry_run:
        action = "would update" if changed else "no change"
        print(f"{action}: version={version}")
    else:
        if changed:
            print(f"Updated platform.txt version to {version}")
        else:
            print(f"platform.txt version already {version}")
    # Always print bare version last so callers can capture it easily.
    print(version)
    return 0

if __name__ == "__main__":
    sys.exit(main())
