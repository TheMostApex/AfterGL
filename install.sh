#!/bin/bash

echo "------------------------------------------"
echo "Starting AfterGL Installation..."
echo "------------------------------------------"

# 1. Ensure dependencies are installed (The 'Careful' way)
echo "Checking system dependencies..."
sudo pacman -S --needed --noconfirm mesa libglvnd glfw-x11 cmake base-devel

# 2. Clean up old failed attempts
if [ -d "build" ]; then
    echo "Cleaning old build directory..."
    rm -rf build
fi

# 3. Create fresh build folder
mkdir build
cd build

# 4. Configure with CMake
echo "Configuring AfterGL..."
cmake ..

# 5. Compile
echo "Compiling AfterGL..."
if make; then
    echo "------------------------------------------"
    echo "Run AfterGL with: ./build/AfterGL"
    echo "------------------------------------------"
else
    echo "Build failed. Check the error message above."
    exit 1
fi
