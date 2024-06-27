/*

Problem Statement: https://codeforces.com/contest/1982/problem/D

First, calculate diff: the difference in sums of snowy mountains and non-snowy.
If diff is 0, then print "YES". For every kxk rectangle, let d be (the absolute
value of) the number of snowy mountains in the rectangle minus the number of
non-snowy mountains in the rectangle. We can find d using 2D prefix sums if we
set all mountains of one type to 1 and all mountains of the other type to -1.
Then, the sum of mountain types in each kxk rectangle will be d.

For every kxk rectangle, we are able to change diff by d by either adding or
subtracting 1 from each mountain in the rectangle. We are also able to change 
diff by c*d if we add/subtract c from each mountain. We can define our new
problem as this: given a set of n integers (S = { v1, v2, ..., vn }) and an 
integer x, determine if it possible to make x 0 by adding or subtracting values
in S to x (the same value can be added/subtracted multiple times). It can be
determined that it is possible if x % gcd(v1, v2, ..., vn) == 0.

*/

#include <iostream>
#include <vector>
#include <string>

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
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<std::vector<int>> heights(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> heights[i][j];
            }
        }
        std::vector<std::string> type(n);
        long long diff = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> type[i];
            for (int j = 0; j < m; ++j) {
                diff += (type[i][j] == '0' ? 1 : -1) * heights[i][j];
            }
        }
        if ((diff = std::abs(diff)) == 0) {
            std::cout << "YES" << '\n';
            continue;
        }
        std::vector<std::vector<int>> p(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
                p[i][j] += type[i - 1][j - 1] == '0' ? 1 : -1;
            }
        }
        int g = 0;
        for (int i = 0; i <= n - k; ++i) {
            for (int j = 0; j <= m - k; ++j) {
                int s = p[i + k][j + k] - p[i][j + k] - p[i + k][j] + p[i][j];
                g = gcd(g, std::abs(s));
            }
        }
        std::cout << (g > 0 && diff % g == 0 ? "YES" : "NO") << '\n';
    }
}
