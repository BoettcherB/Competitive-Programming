/*

Problem Statement: https://codeforces.com/contest/1985/problem/H2

This problem is very similar to the previous problem (H1) except now we are
choosing a row and a column. Since n*m <= 10^6, we can try all possible (r, c)
pairs and pick the best one. However, it is possible that some components are
adjacent to both r and c, so their size will be counted twice. To fix this, we
can set up an array dup[i][j] which is the number of cells that will be counted
twice if we choose row i and column j. A component c's size is included in
dup[i][j] if minX[c]-1 <= i <= maxX[c]+1 and minY[c]-1 <= j <= maxY[c]+1.
dup[i][j] can be found with 2d prefix sums. For each component c, fill in the
rectangle with upper left corner (minX[c] - 1, minY[c] - 1) and lower right
corner (maxX[c] + 1, maxY[c] + 1) with size[c]. Finally, add 1 to dup[i][j] if
cell (i, j) is '.'. Find the answer for row i and column j with adjR[i] + the
number of '.' in row i + adjC[j] + the number of '.' in column j - dup[i][j].
The overall answer is the max of these.

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

typedef std::vector<std::string> Grid;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
Grid g;
int n, m;

void dfs(int x, int y, Comp& c, Grid& g) {
    c.add(x, y);
    g[x][y] = 'X';
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
        g = Grid(n);
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
        for (int i = 0; i < n; ++i) adjRow[i + 1] += adjRow[i];
        for (int i = 0; i < m; ++i) adjCol[i + 1] += adjCol[i];
        std::vector<std::vector<int>> dup(n + 2, std::vector<int>(m + 2));
        for (const Comp& c : comps) {
            for (int i = std::max(0, c.minX - 1); i <= c.maxX + 1; ++i) {
                dup[i][std::max(0, c.minY - 1)] += c.size;
                dup[i][c.maxY + 2] -= c.size;
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dup[i][j + 1] += dup[i][j];
                dup[i][j] += g[i][j] == '.';
                int curRes = adjRow[i] + m - rowCount[i];
                curRes += adjCol[j] + n - colCount[j];
                res = std::max(res, curRes - dup[i][j]);
            }
        }
        std::cout << res << '\n';
    }
}
