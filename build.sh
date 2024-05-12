#!/bin/bash

if [ "$1" == "--clean" ]; then
    echo "Performing a clean build..."
    rm -rf build
    mkdir build
    cd build
    cmake ..
else
    if [ ! -d "build" ]; then
        mkdir build
        cd build
        cmake ..
    else
        cd build
    fi
fi

make


