/*

CSES: Graph Algorithms: Counting Rooms

You are given a grid of nxm cells. Each cell is either empty '.' or a wall '#'.
Your task is to count the number of empty rooms.

Constraints:
    1 <= n, m <= 1000

Example Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Example Output:
3

This problem can be solved with a simple flood fill or dfs algorithm. Loop
through each cell and when we find an empty cell, mark it as a new room. Then,
recursively visit each cell connected to the current cell while filling them in
(as walls) as we go. One simple optimization is to make the grid n+2 x m+2 and
fill in the outer boundary with walls so that we do not have to do any bounds
checking.

*/

#include <iostream>
#include <vector>
#include <string>

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void floodfill(int x, int y, std::vector<std::string>& g) {
    if (g[x][y] == '#') return;
    g[x][y] = '#';
    for (int i = 0; i < 4; ++i) {
        floodfill(x + dx[i], y + dy[i], g);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> g(n + 2);
    g[0] = g[n + 1] = std::string(m + 2, '#');
    for (int i = 1; i <= n; ++i) {
        std::string str;
        std::cin >> str;
        g[i] = '#' + str + '#';
    }
    int comps = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g[i][j] == '.') {
                floodfill(i, j, g);
                ++comps;
            }
        }
    }
    std::cout << comps << '\n';
}
