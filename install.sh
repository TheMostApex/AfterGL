#!/bin/bash

echo "--------------------------------"
echo "Starting AfterGL installalation."
echo "--------------------------------"

echo "Installing system dependencies..."
sudo apt-get update
sudo apt-get install -y libglfw3-dev libgl1-mesa-dev cmake build-essential

# 2. Build the project
echo "Building AfterGL..."
mkdir -p build
cd build
cmake ..
make

# 3. Install to the system
echo "Installing AfterGL to /usr/local..."
sudo make install

echo "Done! You can now link with -laftergl"
