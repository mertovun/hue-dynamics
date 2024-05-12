#!/bin/bash

# This script builds and runs the hue-dynamics project.

# Check for command line argument to perform a clean build
if [ "$1" == "--clean" ]; then
    echo "Performing a clean build..."
    rm -rf build
    mkdir build
    cd build
    cmake ..
else
    # Check if build directory exists, if not, create it and run cmake
    if [ ! -d "build" ]; then
        mkdir build
        cd build
        cmake ..
    else
        cd build
    fi
fi

# Build the project
make

# Run the executable
./hue-dynamics

