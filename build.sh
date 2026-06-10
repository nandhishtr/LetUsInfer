#!/usr/bin/env bash

if [ "$1" == "-c" ]; then
    echo "Clean build in progress"
    rm -rf build
    echo " Clean done"
fi

echo "Configuring build with CMake preset..."
if cmake --preset debug; then
    echo "Configuration successful."
else
    echo "Configuration failed. Aborting."
    exit 1
fi

echo "Building project..."
if cmake --build build/debug; then
    echo "Build successful. Run with: ./build/debug/LetUsInfer"
else
    echo "Build failed."
    exit 1
fi
