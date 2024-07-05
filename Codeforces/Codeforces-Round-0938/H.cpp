/*

Problem Statement: https://codeforces.com/contest/1955/problem/H

For each tower, we can calculate how much damage it will contribute at each
radius r. If tower i does p_i damage and c_ir is the number of path cells
(those with '#') within radius r of tower i, then tower i will contribute
(c_ir * p_i - 3^r) damage to each monster if its radius is set to r. ie.
damage[i][r] = c_ir * p_i - 3^r.

The next thing to realize is that 3^r becomes very large very quickly. We can
calculate the max amount of damage that any tower can do with 500πr^2 There are
at most πr^2 path cells within radius r and a tower can do a maximum of 500
damage per cell. This number is < 3^r if r >= 12. Therefore, we do not have to
worry about r >= 12.

We can use bitmask dp to solve for dp[i][c], which is the maximum damage dealt
by the first i towers if the only radii used are the bits set in c (for example
if c = 111001. Then the only radii used are r=1, r=4, r=5, and r=6). If we
consider setting tower i to radius r, then we need to find every combination of
radii / bitmask c such that the r'th bit in c is 0. Let C = c | (1 << r). C = c
but with the r'th bit set to 1. Then, dp[i][C] = max(dp[i][C], dp[i - 1][c] +
damage[i][r].

The overall runtime is O(k * plog(p) + kr * 2^r) where k is the number of
towers, p is the number of cells on the path, and r is the maximum radius (12).

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

const int R = 12;

int dist(const std::pair<int, int>& c1, const std::pair<int, int>& c2) {
    int xdiff = c1.first - c2.first, ydiff = c1.second - c2.second;
    return xdiff * xdiff + ydiff * ydiff;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<int> healthInc(R);
    for (int r = 1; r < R; ++r) {
        healthInc[r] = (int) std::pow(3, r);
    }
    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<std::pair<int, int>> path;
        for (int i = 0; i < n; ++i) {
            std::string row;
            std::cin >> row;
            for (int j = 0; j < m; ++j) {
                if (row[j] == '#') {
                    path.emplace_back(i, j);
                }
            }
        }
        int cells = (int) path.size();
        std::vector<std::vector<int>> dmg(k + 1, std::vector<int>(R));
        for (int i = 1; i <= k; ++i) {
            int x, y, p;
            std::cin >> x >> y >> p;
            std::pair<int, int> t = { --x, --y };
            std::sort(path.begin(), path.end(), [&](auto& c1, auto& c2) {
                return dist(t, c1) < dist(t, c2);
            });
            int r = 0, inRange = 0;
            while (++r < R) {
                while (inRange < cells && dist(path[inRange], t) <= r * r) {
                    ++inRange;
                }
                dmg[i][r] = inRange * p - healthInc[r];
            }
        }
        int combs = 1 << R;
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(combs));
        for (int i = 1; i <= k; ++i) {
            for (int c = 0; c < combs; ++c) {
                dp[i][c] = std::max(dp[i][c], dp[i - 1][c]);
                for (int r = 0; r < R; ++r) {
                    if (c & (1 << r)) continue;
                    int j = c | (1 << r);
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][c] + dmg[i][r]);
                }
            }
        }
        std::cout << dp[k][combs - 1] << '\n';
    }
}
