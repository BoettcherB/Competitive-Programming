/*

CSES: Graph Algorithms: Monsters

You are given an nxm grid of cells. Each cell is either empty ('.'), a wall
('#'), a monster ('M'), or you ('A'). Every step, you and all the monsters
simultaneously move 1 step in any direction. If you and a monster are in the
same cell at the same time, you lose. Determine if it is possible to reach the
edge of the grid even if the monsters know your path beforehand. If it is not
possible, print "NO". If it is possible, print "YES" followed by a description
of the path you would take.

Constraints:
    1 <= n, m <= 1000
    Each cell is either '.', '#', 'M', or 'A'
    There is exactly one 'A' in the input

Example Input:
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######

Example Output:
YES
5
RRDDR

This can be solved using bfs. We can insert the player and all the monsters
into the queue at the start. We will handle dequeues differently for the player
vs the monsters. For the monsters, if we move to an adjacent cell we will
preemptively mark that cell as visited. That way, on the next turn if a player
is on that cell, we will know that monster is also on that cell. For the player
we first check if the cell is visited. If not, we check if we are on an edge
cell. If not, we move to any non-visited empty adjacent cells and record which
direction we came from ('U', 'D', 'L', or 'R').

Another method is to determine the distance of the player to all edge cells, as
well as the distance of any monster to all edge cells. If there is an edge cell
where the player is closer than all monsters, then the player can exit using
that cell. This method requires running bfs twice.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
char dir[4] = { 'R', 'D', 'L', 'U' };

struct Entity {
    Entity(int x, int y, bool m) : x{ x }, y{ y }, monster{ m } {}
    int x, y;
    bool monster;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> grid(n);
    std::pair<int, int> start;
    std::vector<std::pair<int, int>> monsters;
    for (int i = 0; i < n; ++i) {
        std::cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A')
                start = { i, j };
            else if (grid[i][j] == 'M')
                monsters.emplace_back(i, j);
        }
    }
    std::queue<Entity> q;
    q.emplace(start.first, start.second, false);
    for (auto& m : monsters) {
        q.emplace(m.first, m.second, true);
    }
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
    std::vector<std::vector<char>> prev(n, std::vector<char>(m));
    std::pair<int, int> edge = { -1, -1 };
    while (!q.empty()) {
        Entity e = q.front();
        q.pop();
        if (!e.monster) {
            if (visited[e.x][e.y]) continue;
            if (e.x == 0 || e.y == 0 || e.x == n - 1 || e.y == m - 1) {
                edge = { e.x, e.y };
                break;
            }
        }
        visited[e.x][e.y] = true;
        for (int i = 0; i < 4; ++i) {
            int x = e.x + dx[i], y = e.y + dy[i];
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            if (visited[x][y] || grid[x][y] == '#') continue;
            if (e.monster) {
                visited[x][y] = true;
                q.emplace(x, y, true);
            } else {
                prev[x][y] = dir[i];
                q.emplace(x, y, false);
            }
        }
    }
    if (edge == std::make_pair(-1, -1)) {
        std::cout << "NO" << '\n';
        return 0;
    }
    std::string path;
    while (edge != start) {
        char d = prev[edge.first][edge.second];
        path += d;
        if (d == 'U') ++edge.first;
        if (d == 'D') --edge.first;
        if (d == 'L') ++edge.second;
        if (d == 'R') --edge.second;
    }
    std::reverse(path.begin(), path.end());
    std::cout << "YES" << '\n' << path.length() << '\n' << path << '\n';
}
