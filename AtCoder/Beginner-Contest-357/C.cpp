#include <iostream>
#include <cmath>
#include <cstring>

const int N = 1000;
char grid[N][N];

void rec(int level, int x, int y) {
    if (level <= 0) {
        grid[x][y] = '#';
        return;
    }
    if (level == 1) {
        for (int i = x; i < x + 3; ++i) {
            for (int j = y; j < y + 3; ++j) {
                if (i == x + 1 && j == y + 1)
                    continue;
                grid[i][j] = '#';
            }
        }
        return;
    }
    int offs = (int) std::pow(3, level - 1);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1)
                continue;
            rec(level - 1, x + i * offs, y + j * offs);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    int size = (int) std::pow(3, n);
    std::memset(grid, '.', sizeof(grid));
    rec(n, 0, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << grid[i][j];
        std::cout << '\n';
    }
}
