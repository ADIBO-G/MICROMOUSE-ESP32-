#!/usr/bin/env bash
# Build and run every unit test on your PC. No hardware needed.
set -e
mkdir -p build
g++ -std=c++17 -Wall -Wextra -O2 -I firmware/lib/maze tests/test_maze.cpp -o build/test_maze
./build/test_maze
