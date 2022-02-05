#!/bin/sh
cmake -S . -B build -G Ninja && \
    cmake --build build -j16 && \
    ./build/app