#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
BUILD_DIR="$SCRIPT_DIR/build"

if [ ! -d "$BUILD_DIR" ] || [ "$1" == "--force" ]; then
    cmake -B "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=on .
fi

make -C "$BUILD_DIR"
