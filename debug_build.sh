#!/bin/bash

# Set build directory
BUILD_DIR="build"

# Clear existing build
echo "🧹 Cleaning $BUILD_DIR..."
rm -rf "$BUILD_DIR"

# Create build directory
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

# Run CMake with Debug configuration
echo "🛠️  Configuring with CMake (Debug build)..."
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
echo "📦 Building..."
make -j$(nproc)

# Done
echo "✅ Debug build complete: $BUILD_DIR/dft_util"
