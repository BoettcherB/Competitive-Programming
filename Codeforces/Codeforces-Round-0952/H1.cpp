/*

Problem Statement: https://codeforces.com/contest/1985/problem/H1

For this problem, we need to find the size of each component, as well as their
min and max row and min and max column. All of these can be found using dfs.

Next, let adjR[i] be the sum of the sizes of components that are adjacent to
row i. A component is adjacent to row i if it will be included in the component
formed when setting every cell of row i to '#'. Specifically, component c is
adjacent to row i if minX[c] - 1 <= i <= maxX[c] + 1. Similarly, let adjC[j] be
the sum of the sizes of components that are adjacent to column j. Component c
is adjacent to column j if minY[c] - 1 <= i <= maxY[c] + 1. We can find adjR[i]
and adjC[j] for all i and j using prefix sums. For each component c, set
adjR[minX[c] - 1] to size[c] and adjR[maxX[c] + 2] to -size[c]. Then, compute
the prefix sum of adjR. Do the same for adjC.

Now we need to try out every row and every column. If we choose row i, then the
answer is adjR[i] + the number of cells containing '.' in row i. Similarly, if
we choose column, j, the answer is adjC[j] + the number of cells containing '.'
in column j. The answer is the maximum of these.

*/

#include <iostream>
#include <vector>
#include <string>

struct Comp {
    int size, minX, maxX, minY, maxY;
    Comp() {
        size = 0;
        minX = minY = 2e9;
        maxX = maxY = -2e9;
    }
    void add(int x, int y) {
        ++size;
        minX = std::min(x, minX);
        maxX = std::max(x, maxX);
        minY = std::min(y, minY);
        maxY = std::max(y, maxY);
    }
};

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
std::vector<std::string> g;
int n, m;

void dfs(int x, int y, Comp& c, std::vector<std::string>& g) {
    c.add(x, y);
    g[x][y] = '.';
    for (int i = 0; i < 4; ++i) {
        int X = x + dx[i], Y = y + dy[i]; 
        if (X >= 0 && Y >= 0 && X < n && Y < m && g[X][Y] == '#') {
            dfs(X, Y, c, g);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::cin >> n >> m;
        g = std::vector<std::string>(n);
        std::vector<int> rowCount(n), colCount(m);
        for (int i = 0; i < n; ++i) {
            std::cin >> g[i];
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == '#') {
                    ++rowCount[i];
                    ++colCount[j];
                }
            }
        }
        std::vector<Comp> comps;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == '#') {
                    Comp c;
                    dfs(i, j, c, g);
                    comps.push_back(c);
                }
            }
        }
        std::vector<int> adjRow(n + 2), adjCol(m + 2);
        for (const Comp& c : comps) {
            adjRow[std::max(0, c.minX - 1)] += c.size;
            adjRow[c.maxX + 2] -= c.size;
            adjCol[std::max(0, c.minY - 1)] += c.size;
            adjCol[c.maxY + 2] -= c.size;
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, adjRow[i] + m - rowCount[i]);
            adjRow[i + 1] += adjRow[i];
        }
        for (int i = 0; i < m; ++i) {
            res = std::max(res, adjCol[i] + n - colCount[i]);
            adjCol[i + 1] += adjCol[i];
        }
        std::cout << res << '\n';
    }
}
