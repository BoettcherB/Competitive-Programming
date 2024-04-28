/*

There are n coins, each with a positive integer value c_i. Using these coins,
find the minimum number of coins needed to produce the sum x. If it is not
possible to produce x, print -1.

Constraints:
    1 <= n <= 100
    1 <= x <= 1,000,000
    1 <= c_i <= 1,000,000

Example Input:
3 11
1 5 7

Example Output:
3

Let dp[i] be the minimum number of coins needed to produce the sum i. We start
by setting dp[c_i] = 1 for all c_i. Then, we can find dp[i] for all values of i
by finding dp[i - c_i] + 1 for all coins c_i and taking the minimum of these.

*/

#include <iostream>
#include <algorithm>

const int N = 1e6 + 10;
const int INF = 2e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, coins[N], dp[N];
    std::cin >> n >> x;
    std::fill(dp, dp + N, INF);
    for (int i = 0; i < n; ++i) {
        std::cin >> coins[i];
        dp[coins[i]] = 1;
    }
    for (int i = 1; i <= x; ++i) {
        if (dp[i] != INF)
            continue;
        for (int j = 0; j < n; ++j) {
            int i2 = i - coins[j];
            if (i2 >= 0 && dp[i2] != INF) {
                dp[i] = std::min(dp[i], dp[i2] + 1);
            }
        }
    }
    std::cout << (dp[x] == INF ? -1 : dp[x]) << '\n';
}
