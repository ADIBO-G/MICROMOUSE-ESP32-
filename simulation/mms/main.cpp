// Micromouse flood fill for the mms simulator (C++)
// Maze logic (struct Maze) never calls the simulator, so the same code can later run on the ESP32.
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "API.h"

constexpr int MAXN = 16;
enum Dir { N = 0, E = 1, S = 2, W = 3 };
constexpr int DX[4] = {0, 1, 0, -1};
constexpr int DY[4] = {1, 0, -1, 0};
constexpr char DCHAR[4] = {'n', 'e', 's', 'w'};

struct Cell { int x, y; };

// ---------------------------------------------------------------- pure maze logic
struct Maze {
    int w, h;
    bool wall[MAXN][MAXN][4];
    int dist[MAXN][MAXN];

    Maze(int w_, int h_) : w(w_), h(h_) {
        for (int x = 0; x < MAXN; x++)
            for (int y = 0; y < MAXN; y++) {
                dist[x][y] = -1;
                for (int d = 0; d < 4; d++) wall[x][y][d] = false;
            }
        for (int x = 0; x < w; x++) { wall[x][0][S] = true; wall[x][h - 1][N] = true; }
        for (int y = 0; y < h; y++) { wall[0][y][W] = true; wall[w - 1][y][E] = true; }
    }

    bool inBounds(int x, int y) const { return x >= 0 && y >= 0 && x < w && y < h; }

    // store the wall on BOTH sides of the boundary
    void addWall(int x, int y, int d) {
        wall[x][y][d] = true;
        int nx = x + DX[d], ny = y + DY[d];
        if (inBounds(nx, ny)) wall[nx][ny][(d + 2) % 4] = true;
    }

    // BFS outward from the goal cells
    void flood(const std::vector<Cell>& goals) {
        for (int x = 0; x < w; x++)
            for (int y = 0; y < h; y++) dist[x][y] = -1;
        std::queue<Cell> q;
        for (const Cell& g : goals) { dist[g.x][g.y] = 0; q.push(g); }
        while (!q.empty()) {
            Cell c = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                if (wall[c.x][c.y][d]) continue;
                int nx = c.x + DX[d], ny = c.y + DY[d];
                if (inBounds(nx, ny) && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[c.x][c.y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    // open neighbour with the smallest number (-1 if none)
    int bestDir(int x, int y) const {
        int best = -1, bestD = 1 << 30;
        for (int d = 0; d < 4; d++) {
            if (wall[x][y][d]) continue;
            int nx = x + DX[d], ny = y + DY[d];
            if (inBounds(nx, ny) && dist[nx][ny] >= 0 && dist[nx][ny] < bestD) {
                best = d; bestD = dist[nx][ny];
            }
        }
        return best;
    }
};

// ---------------------------------------------------------------- simulator glue
void log(const std::string& s) { std::cerr << s << std::endl; }

void sense(Maze& m, int x, int y, int heading) {
    auto save = [&](int d) { m.addWall(x, y, d); API::setWall(x, y, DCHAR[d]); };
    if (API::wallFront()) save(heading);
    if (API::wallLeft())  save((heading + 3) % 4);
    if (API::wallRight()) save((heading + 1) % 4);
}

int face(int heading, int target) {
    int diff = (target - heading + 4) % 4;
    if (diff == 1)      API::turnRight();
    else if (diff == 2) { API::turnRight(); API::turnRight(); }
    else if (diff == 3) API::turnLeft();
    return target;
}

bool isGoal(const std::vector<Cell>& goals, int x, int y) {
    for (const Cell& g : goals) if (g.x == x && g.y == y) return true;
    return false;
}

// drive from (x,y,heading) until a goal cell is reached; returns number of moves
int runTo(Maze& m, const std::vector<Cell>& goals, int& x, int& y, int& heading) {
    int moves = 0;
    while (!isGoal(goals, x, y)) {
        sense(m, x, y, heading);
        m.flood(goals);
        for (int gx = 0; gx < m.w; gx++)
            for (int gy = 0; gy < m.h; gy++) API::setText(gx, gy, std::to_string(m.dist[gx][gy]));
        int d = m.bestDir(x, y);
        if (d < 0) { log("No path found"); break; }
        heading = face(heading, d);
        API::moveForward();
        x += DX[heading]; y += DY[heading];
        moves++;
    }
    return moves;
}

int main() {
    Maze maze(API::mazeWidth(), API::mazeHeight());
    int cx = maze.w / 2, cy = maze.h / 2;
    std::vector<Cell> center = {{cx - 1, cy - 1}, {cx - 1, cy}, {cx, cy - 1}, {cx, cy}};
    std::vector<Cell> start = {{0, 0}};

    int x = 0, y = 0, heading = N;

    int m1 = runTo(maze, center, x, y, heading);   // search run
    log("Reached centre in " + std::to_string(m1) + " moves");
    API::setColor(x, y, 'G');

    int m2 = runTo(maze, start, x, y, heading);    // return run
    log("Back at start in " + std::to_string(m2) + " moves");
    API::setColor(x, y, 'B');

    int m3 = runTo(maze, center, x, y, heading);   // second run on the learned map
    log("Second run to centre in " + std::to_string(m3) + " moves");
    API::setColor(x, y, 'G');
    return 0;
}
