#include <iostream>
#include <string>
#include <vector>
#include <queue>

const int N = 1010;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
bool grid[N][N];
int res[N][N];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        std::string row;
        std::cin >> row;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = row[j] == '.';
        }
    }
    for (int t = 0; t < k; ++t) {
        int sx, sy;
        std::cin >> sx >> sy;
        if (res[--sx][--sy] > 0) {
            std::cout << res[sx][sy] << '\n';
            continue;
        }
        std::vector<std::pair<int, int>> filled;
        std::queue<std::pair<int, int>> q;
        q.emplace(sx, sy);
        int walls = 0;
        while (!q.empty()) {
            std::pair<int, int> cur = q.front();
            int x = cur.first, y = cur.second;
            q.pop();
            if (res[x][y])
                continue;
            res[x][y] = 1;
            filled.push_back(cur);
            for (int i = 0; i < 4; ++i) {
                int X = x + dx[i], Y = y + dy[i];
                if (!grid[X][Y])
                    ++walls;
                else if (!res[X][Y])
                    q.emplace(X, Y);
            }
        }
        for (const std::pair<int, int>& cell : filled) {
            res[cell.first][cell.second] = walls;
        }
        std::cout << walls << '\n';
    }
}
