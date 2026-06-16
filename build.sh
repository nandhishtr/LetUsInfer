#!/usr/bin/env bash

PRESET="debug"

if [[ "$1" == "--release" || "$2" == "--release" ]]; then
    PRESET="release"
fi 

if [[ "$1" == "-c" || "$2" == "-c" ]]; then
    echo "Clean build in progress"
    rm -rf build/${PRESET}
    echo "Clean done"
fi

echo "Configuring build with CMake preset...${PRESET}"
if cmake --preset ${PRESET}; then
    echo "${PRESET} configuration successful."
else
    echo "${PRESET} configuration failed. Aborting."
    exit 1
fi

echo "Building project..."
if cmake --build build/${PRESET}; then
    echo "Build successful. Run with: ./build/${PRESET}/LetUsInfer"
else
    echo "Build failed."
    exit 1
fi
