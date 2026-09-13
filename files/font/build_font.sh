#!/bin/sh

BASE_DIR="$(cd -- "$(dirname -- "$0")" && pwd)"
OUTPUT="$BASE_DIR/../../src/font.c"

echo "Checking for xxd"

if command -v xxd >/dev/null 2>&1; then
  echo "Running xxd -i on .ttf files"

  : >"$OUTPUT"

  (
    cd "$BASE_DIR" || exit 1

    for font in *.ttf; do
      [ -f "$font" ] || continue
      xxd -i "$font" >>"$OUTPUT"
    done
  )

else
  echo "Cannot find xxd, required for install"
  echo "Using Premade Bytecode For Font Files"
fi
