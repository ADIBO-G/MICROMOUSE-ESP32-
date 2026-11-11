# Simulation

Everything in this folder runs on your computer, so no robot is needed.

## mms (the maze simulator)

[`mms/main.cpp`](mms/main.cpp) is flood fill in C++ for the [mms simulator](https://github.com/mackorone/mms):
search run to the centre, return run to the start, then a second run on the learned map.

1. Install mms and add a new C++ algorithm.
2. Replace the template `main.cpp` with [`mms/main.cpp`](mms/main.cpp) (keep the `API.h` and build settings mms gives you).
3. Pick a maze and press Run. The numbers on the cells are the flood-fill distances.

`mms/main.cpp` is a standalone copy of the maze logic. The tested, reusable version lives in
[`firmware/lib/maze/maze.h`](../firmware/lib/maze/maze.h).

## Status

- [x] Compiles and runs against a stub maze (logic checked: centre in 7, back in 15, again in 7 moves on an 8x8 test maze)
- [ ] Run inside mms on the standard test mazes (milestone M3)
