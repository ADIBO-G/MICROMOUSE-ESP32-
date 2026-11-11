// Unit tests for firmware/lib/maze/maze.h. No framework: each test prints PASS or stops with FAIL.
// Milestone M2 in docs/roadmap.md.
#include <cstdio>
#include <cstdlib>
#include "maze.h"
using namespace mm;

static int checks = 0;
#define CHECK(cond) do { checks++; if (!(cond)) { std::printf("FAIL line %d: %s\n", __LINE__, #cond); std::exit(1); } } while (0)

static void test_empty_room_is_manhattan() {
    Maze m(6, 6); Cell g[] = {{4, 1}};
    m.flood(g, 1);
    for (int x = 0; x < 6; x++)
        for (int y = 0; y < 6; y++)
            CHECK(m.distance(x, y) == std::abs(x - 4) + std::abs(y - 1));
    std::puts("PASS  empty room gives Manhattan distances");
}

static void test_wall_raises_numbers_like_the_notes() {
    // The 4x4 example from the notes (Figure 3.2a), goal in the top-right corner.
    Maze m(4, 4); Cell g[] = {{3, 3}};
    for (int y = 1; y <= 3; y++) m.addWall(2, y, E);      // wall between x=2 and x=3, gap in the bottom row
    m.flood(g, 1);
    const int expect[4][4] = {  // expect[row from the top][x]
        {9, 8, 7, 0}, {8, 7, 6, 1}, {7, 6, 5, 2}, {6, 5, 4, 3}};
    for (int row = 0; row < 4; row++)
        for (int x = 0; x < 4; x++)
            CHECK(m.distance(x, 3 - row) == expect[row][x]);
    std::puts("PASS  wall forces a detour: numbers match the notes");
}

static void test_wall_stored_on_both_sides() {
    Maze m(6, 6);
    m.addWall(2, 2, E);
    CHECK(m.wall(2, 2, E));
    CHECK(m.wall(3, 2, W));
    CHECK((m.wallBits(2, 2) & 2) != 0 && (m.wallBits(3, 2) & 8) != 0);   // E = 2, W = 8
    std::puts("PASS  wall stored on both sides (bitmask E=2, W=8)");
}

static void test_following_best_dir_reaches_goal_in_dist_steps() {
    Maze m(6, 6); Cell g[] = {{4, 1}};
    for (int y = 1; y <= 5; y++) m.addWall(2, y, E);
    m.flood(g, 1);
    for (int sx = 0; sx < 6; sx++)
        for (int sy = 0; sy < 6; sy++) {
            int x = sx, y = sy, steps = 0, want = m.distance(sx, sy);
            while (!(x == 4 && y == 1)) {
                int d = m.bestDir(x, y);
                CHECK(d >= 0);
                x += DX[d]; y += DY[d]; steps++;
                CHECK(steps <= 100);
            }
            CHECK(steps == want);
        }
    std::puts("PASS  walking downhill reaches the goal in exactly 'distance' steps");
}

static void test_adding_walls_never_lowers_numbers() {
    Maze m(8, 8); Cell g[] = {{3, 3}, {3, 4}, {4, 3}, {4, 4}};
    m.flood(g, 4);
    int before[8][8];
    unsigned seed = 12345;
    for (int k = 0; k < 40; k++) {
        for (int x = 0; x < 8; x++) for (int y = 0; y < 8; y++) before[x][y] = m.distance(x, y);
        seed = seed * 1664525u + 1013904223u;
        int x = (seed >> 8) % 8, y = (seed >> 16) % 8, d = (seed >> 24) % 4;
        m.addWall(x, y, d);
        m.flood(g, 4);
        for (int a = 0; a < 8; a++)
            for (int b = 0; b < 8; b++)
                if (before[a][b] >= 0 && m.distance(a, b) >= 0) CHECK(m.distance(a, b) >= before[a][b]);
    }
    std::puts("PASS  adding a wall never lowers a number");
}

// A virtual 6x6 maze that plays the role of the real walls the mouse can feel.
struct Virtual {
    Maze truth{6, 6};
    Virtual() { for (int y = 1; y <= 5; y++) truth.addWall(2, y, E); truth.addWall(3, 3, S); truth.addWall(4, 3, S); }
};

static void test_search_run_reaches_goal_on_a_virtual_maze() {
    Virtual v; Maze known(6, 6); Cell goal[] = {{4, 1}};
    int x = 0, y = 0, steps = 0;
    while (!(x == 4 && y == 1)) {
        for (int d = 0; d < 4; d++) if (v.truth.wall(x, y, d)) known.addWall(x, y, d);   // "sense"
        known.flood(goal, 1);
        int d = known.bestDir(x, y);
        CHECK(d >= 0);
        CHECK(!v.truth.wall(x, y, d));                  // never drives through a real wall
        x += DX[d]; y += DY[d]; steps++;
        CHECK(steps < 200);
    }
    CHECK(steps >= 4 + 1);                              // never shorter than the Manhattan distance
    std::printf("PASS  search run reaches the goal on a virtual maze (%d moves)\n", steps);
}

int main() {
    test_empty_room_is_manhattan();
    test_wall_raises_numbers_like_the_notes();
    test_wall_stored_on_both_sides();
    test_following_best_dir_reaches_goal_in_dist_steps();
    test_adding_walls_never_lowers_numbers();
    test_search_run_reaches_goal_on_a_virtual_maze();
    std::printf("\nAll tests passed (%d checks).\n", checks);
    return 0;
}
