#include <iostream>
#include <vector>
#include <set>
#include <queue>

struct Cell {
    int x, y, h;
    Cell(int x, int y, int h) : x{ x }, y{ y }, h{ h } {}
    bool operator<(const Cell& o) const {
        return h == o.h ? (x == o.x ? y < o.y : x < o.x) : h < o.h;
    }
};

const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, H;
    std::cin >> n >> m >> H;
    std::vector<std::vector<int>> grid(n + 2, std::vector<int>(m + 2));
    std::set<Cell> adjWater;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> grid[i][j];
            if (i == 1 || i == n || j == 1 || j == m)
                adjWater.emplace(i, j, grid[i][j]);
        }
    }
    int res = n * m;
    for (int h = 1; h <= H; ++h) {
        std::queue<Cell> q;
        while (!adjWater.empty() && adjWater.begin()->h <= h) {
            if (grid[adjWater.begin()->x][adjWater.begin()->y] != 0)
                q.emplace(*adjWater.begin());
            adjWater.erase(adjWater.begin());
        }
        while (!q.empty()) {
            Cell cur = q.front();
            q.pop();
            if (grid[cur.x][cur.y] == 0)
                continue;
            grid[cur.x][cur.y] = 0;
            --res;
            for (int d = 0; d < 4; ++d) {
                int x = cur.x + dx[d], y = cur.y + dy[d];
                if (grid[x][y] != 0) {
                    adjWater.emplace(x, y, grid[x][y]);
                    if (grid[x][y] <= h)
                        q.emplace(x, y, grid[x][y]);
                }
            }
        }
        std::cout << res << '\n';
    }
}
