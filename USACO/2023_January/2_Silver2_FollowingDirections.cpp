/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1279

Keep two 2d arrays: grid[][] to hold the directions of each cell and the cost
of the feeding vats, and cows[][] to hold the number of cows that pass through
each cell. We can fill in cows[][] using dp: starting at the top left, for
every cell (i,j), cows[i][j] is initially 1. If cows[i - 1][j] is pointing
down, then cows[i][j] += cows[i - 1][j]. If cows[i][j - 1] is pointing right,
then do cows[i][j] += cows[i][j - 1]. The number of cows at a feeding vat is
either equal to the number of cows at the adjacent cell or 0, depending on the
direction of the adjacent cell.

When updating the direction of a cell, we only have to update the number of
cows along the paths exiting that cell. If the direction of cell (i,j) changes
to RIGHT, we add the value of cows[i][j] to every cell along the path starting
at cell (i,j+1), and we subtract the value of cows[i][j] from every cell along
the path starting at cell (i+1,j). There is only 1 path from a cell to a vat,
so these updates are only O(n) each.

*/

#include <iostream>
#include <string>

#define RIGHT 1
#define DOWN 2
const int N = 1510;
int n, grid[N][N], cows[N][N];

int total_cost() {
    int cost = 0;
    for (int x = 1; x <= n; ++x) {
        cows[x][n + 1] = (grid[x][n] == RIGHT ? cows[x][n] : 0);
        cows[n + 1][x] = (grid[n][x] == DOWN ? cows[n][x] : 0);
        cost += cows[x][n + 1] * grid[x][n + 1];
        cost += cows[n + 1][x] * grid[n + 1][x];
    }
    return cost;
}

void update_path(int i, int j, int amount) {
    while (i <= n && j <= n) {
        cows[i][j] += amount;
        if (grid[i][j] == RIGHT)
            ++j;
        else
            ++i;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::string str;
        std::cin >> str >> grid[i][n + 1];
        for (int j = 1; j <= n; ++j) {
            grid[i][j] = str[j - 1] == 'R' ? RIGHT : DOWN;
        }
    }
    for (int j = 1; j <= n; ++j) {
        std::cin >> grid[n + 1][j];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cows[i][j] = 1;
            if (i > 1 && grid[i - 1][j] == DOWN)
                cows[i][j] += cows[i - 1][j];
            if (j > 1 && grid[i][j - 1] == RIGHT)
                cows[i][j] += cows[i][j - 1];
        }
    }
    std::cout << total_cost() << '\n';
    int q;
    std::cin >> q;
    while (q--) {
        int I, J;
        std::cin >> I >> J;
        if (grid[I][J] == RIGHT) {
            grid[I][J] = DOWN;
            update_path(I, J + 1, -cows[I][J]);
            update_path(I + 1, J, cows[I][J]);
        } else {
            grid[I][J] = RIGHT;
            update_path(I, J + 1, cows[I][J]);
            update_path(I + 1, J, -cows[I][J]);
        }
        std::cout << total_cost() << '\n';
    }
}
