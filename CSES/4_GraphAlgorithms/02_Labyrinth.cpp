/*

You are given an nxm grid of cells. Some cells are empty '.' and some cells are
walls '#'. There is a start cell 'A' and an end cell 'B'. Your task is to find
the shortest path from the start to the end. If such a path exists, print "YES"
followed by the path's length and a description of the path (made up of the
characters L, R, U, and D). If there is no path from 'A' to 'B', print "NO".

Constraints:
    1 <= n, m <= 1000
    Each cell is either '.', '#', 'A', or 'B'.
    There is exactly one 'A' and one 'B'.

Example Input:

5 8
########
#.A#...#
#.##.#B#
#......#
########

Example Output:
YES
9
LDDRRRRRU

This is a standard shortest path problem that can be solved with bfs. First,
insert the starting cell into a queue. Then, for each cell in the queue, check
if it is a wall or if it has already been visited. If not, check the current
cell's neighbors, and if they are not walls then add them to the queue.
Continue until the end cell is found.

To reconstruct the path from A to B, we need to record, for each cell, which
direction we came from to reach the cell. Then, once B is found, we can start
at B and backtrack using those directions until we find A, building the path
as a string as we go.

One small optimization is to make the grid n+2 x m+2 (instead of nxm) and then
fill in the boundaries with walls. This way, we do not have to do any bounds
checking.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> g(n + 2), move(n + 2);
    for (int i = 0; i < n + 2; ++i) {
        g[i] = move[i] = std::vector<char>(m + 2, '#');
    }
    std::pair<int, int> start, end;
    for (int i = 1; i <= n; ++i) {
        std::string str;
        std::cin >> str;
        for (int j = 1; j <= m; ++j) {
            g[i][j] = str[j - 1];
            if (str[j - 1] == 'A') start = { i, j };
            if (str[j - 1] == 'B') end = { i, j };
        }
    }
    std::queue<std::pair<std::pair<int, int>, char>> q;
    q.emplace(start, 'X');
    while (!q.empty()) {
        auto elem = q.front();
        q.pop();
        int x = elem.first.first, y = elem.first.second;
        if (move[x][y] != '#')
            continue;
        move[x][y] = elem.second;
        if (elem.first == end)
            break;
        if (g[x - 1][y] != '#') q.push({{ x - 1, y }, 'U' });
        if (g[x + 1][y] != '#') q.push({{ x + 1, y }, 'D' });
        if (g[x][y - 1] != '#') q.push({{ x, y - 1 }, 'L' });
        if (g[x][y + 1] != '#') q.push({{ x, y + 1 }, 'R' });
    }
    if (move[end.first][end.second] == '#') {
        std::cout << "NO" << '\n';
        return 0;
    }
    std::string path;
    std::pair<int, int> cur = end;
    while (cur != start) {
        char m = move[cur.first][cur.second];
        path.push_back(m);
        if (m == 'U') ++cur.first;
        if (m == 'D') --cur.first;
        if (m == 'L') ++cur.second;
        if (m == 'R') --cur.second;
    }
    std::reverse(path.begin(), path.end());
    std::cout << "YES" << '\n' << path.length() << '\n' << path << '\n';
}
