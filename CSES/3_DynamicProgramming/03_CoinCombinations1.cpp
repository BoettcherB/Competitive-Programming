/*

There are n coins, each with a positive integer value c_i. Using these coins,
find the number of distinct ways that you can produce the sum x.

Constraints:
    1 <= n <= 100
    1 <= x <= 1,000,000
    1 <= c_i <= 1,000,000

Example Input:
3 9
2 3 5

Output:
8

Let dp[i] be the number of ways to make the sum i with the given coins. First,
set dp[c_i] = 1 for all c_i. Then, dp[i] = dp[i - c_1] + ... + dp[i - c_n].

*/

#include <iostream>
 
const int N = 1e6 + 10;
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
        dp[coins[i]] = 1;
    }
    for (int i = 1; i <= x; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i - coins[j] >= 0) {
                dp[i] = (dp[i] + dp[i - coins[j]]) % MOD;
            }
        }
    }
    std::cout << dp[x] << '\n';
}
