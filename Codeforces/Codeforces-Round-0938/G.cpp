/*

Problem Statement: https://codeforces.com/contest/1955/problem/G

Trying a greedy method to select the best gcd at each cell does not work, and 
trying to keep a set of all possible gcd's at each cell is too slow. We have to
realize that it is possible to determine, in O(nm) time, whether a path exists
where all values are divisible by x. Keep a 2D boolean array where true means
there is a path to the current cell where all numbers along the path are
divisible by x. Update using dp by checking if either of the cells to the left
or up are 'true' and if the current cell is divisible by x (grid[i][j]%x == 0).

Now, we need to find the best value of x. We cannot use binary search because
there will be some numbers < x that do not form such a path, and we obviously
cannot try all values 1 <= x <= 10^6. We know that the path must go through
the top left cell and the bottom right cell, and x must divide both of those
values. Therefore, it is sufficient to find the best value x within the
divisors of the greatest common divisor of the top left cell and the bottom
right cell (The maximum number of divisors is 240 for the value 720720).

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef std::vector<std::vector<int>> Grid;
const int N = 101;
int n, m, grid[N][N], dp[N][N];

bool good(int x) {
    dp[0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]) && grid[i][j] % x == 0;
        }
    }
    return dp[n][m];
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                std::cin >> grid[i][j];
            }
        }
        int g = gcd(grid[1][1], grid[n][m]);
        int s = std::sqrt(g);
        std::vector<int> div = { g };
        for (int i = 2; i <= s; ++i) {
            if (g % i == 0) {
                div.push_back(i);
                int d = g / i;
                if (d != i) {
                    div.push_back(d);
                }
            }
        }
        std::sort(div.rbegin(), div.rend());
        int res = 1;
        for (int x : div) {
            if (good(x)) {
                res = x;
                break;
            }
        }
        std::cout << res << '\n';
    }
}
