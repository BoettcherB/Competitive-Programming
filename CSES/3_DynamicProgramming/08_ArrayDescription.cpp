/*

There is an array of length n with numbers between 1 and m. The absolute
difference between 2 adjacent values is at most 1. You are given some of the
digits of the array, while others are unknown. Your task is to count the number
of ways that you could fill in the missing digits. A missing digit is given as
0.

Constaints:
    1 <= n <= 100,000
    1 <= m <= 100

Example Input:
3 5
2 0 2

Output:
3

Let dp[i][j] be the number of ways to fill in the missing digits where the
array ends with digit j and considering only the first i digits. The main idea
is that if an array ends on digit j, then the previous number can only be j,
j-1, or j+1. Start off by setting all dp[i][j] to 0. If the first digit k is
known, set dp[1][k] to 1. If the first digit is not known, set all dp[1][j] to
1. Then, for every digit i, set dp[i][j] = dp[i-1][j-1] + dp[i-1][j] +
dp[i-1][j+1]. If the digit is known, do this for only the known digit. If the
digit is not known, do this for all digits.

*/

#include <iostream>

const int N = 1e5 + 10;
const int M = 110;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, known[N];
    std::cin >> n >> m;
    long long dp[N][M] = { 0 };
    for (int i = 1; i <= n; ++i) {
        std::cin >> known[i];
    }
    for (int j = 1; j <= m; ++j) {
        dp[1][j] = known[1] == j || known[1] == 0;
    }
    for (int i = 2; i <= n; ++i) {
        if (known[i] != 0) {
            int j = known[i];
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1];            
            dp[i][j] %= MOD;
            continue;
        }
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1];
            dp[i][j] %= MOD;
        }
    }
    long long res = 0;
    for (int j = 1; j <= m; ++j) {
        res = (res + dp[n][j]) % MOD;
    }
    std::cout << res << '\n';
}
