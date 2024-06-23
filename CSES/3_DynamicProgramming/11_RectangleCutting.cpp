/*

CSES: Dynamic Programming: Rectangle Cutting

You are given a rectangle of size axb. Your task is to split it into squares
such that all side lengths remain integers, and find the minimum number of cuts
required.

Constraints:
    1 <= a, b <= 500

Example Input:
3 5

Example Output:
3

Let dp[i][j] be the minimum number of cuts required for a rectangle of size
ixj. We can loop through all possible cuts of the rectangle and find the best
one. For example, if we cut at i = 1, then dp[i][j] = dp[1][j] + dp[i - 1][j]
+ 1. We then try all values of i up to i/2, and the same for j. It is also
important to note that dp[i][j] is the same as dp[j][i], so we only need to
check rectangles where i < j.



*/

#include <iostream>

const int N = 510;
const int INF = 2e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int a, b, dp[N][N];
    std::cin >> a >> b;
    if (a > b) {
        std::swap(a, b);
    }
    for (int i = 1; i < N; ++i) {
        dp[1][i] = dp[i][1] = i - 1;
        dp[i][i] = 0;
    }
    for (int i = 2; i <= a; ++i) {
        for (int j = i + 1; j <= b; ++j) {
            dp[i][j] = INF;
            for (int k = 1; k <= i / 2; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }
            for (int k = 1; k <= j / 2; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
            dp[j][i] = dp[i][j];
        }
    }
    std::cout << dp[a][b] << '\n';
}
