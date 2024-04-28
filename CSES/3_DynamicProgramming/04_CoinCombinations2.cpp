/*

There are n coins, each with a positive integer value c_i. Using these coins,
find the number of distinct ORDERED ways that you can produce the sum x.

Constraints:
    1 <= n <= 100
    1 <= x <= 1,000,000
    1 <= c_i <= 1,000,000

Example Input:
3 9
2 3 5

Output:
3

This problem is very similar to the previous problem, except now we need to
consider one coin at a time. If we do this, it is not possible to get multiple
different orderings (ex: 2+1 and 1+2).

Let dp[i] be the number of ordered ways to make the sum i. For every coin c_j,
do the following: Increment dp[c_j] by 1, then loop through all i (1 <= n <= x)
and perform the operation dp[i] += dp[i - c_1] + ... + dp[i - c_n].

*/

#include <iostream>

const int N = 1e6+ 10;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, coins[N];
    long long dp[N] = { 0 };
    std::cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        std::cin >> coins[i];
    }
    for (int j = 0; j < n; ++j) {
        dp[coins[j]] += 1;
        for (int i = 1; i <= x; ++i) {
            if (i - coins[j] >= 0) {
                dp[i] = (dp[i] + dp[i - coins[j]]) % MOD;
            }
        }
    }
    std::cout << dp[x] << '\n';
}
