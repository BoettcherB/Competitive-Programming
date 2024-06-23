/*

CSES: Dynamic Programming: Counting Towers

Your task is to build a tower of height n and width 2. You can use any blocks
with integer height and width. How many different ways are there to build the
tower? Do this for t test cases, and print the answer modulo 1e9+7.

Constraints:
    1 <= t <= 100
    1 <= n <= 1,000,000

Example Input:
3
2
6
1337

Example Output:
8
2864
640403945

Let dp[i][0] be the number of ways to build a tower of height i where the top
of the tower is not connected, and let dp[i][1] be the number of ways to build
a tower of height i where the top of the tower is connected. If the top of the
previous tower is not connected, we can either place two 1x1 blocks as the new
layer, extend the left block up by 1, extend the right block up by 1, or extend
both blocks up by 1. We can also place two 1x1 blocks on top of a connected
layer. Therefore, dp[i][0] = dp[i-1][0] * 4 + dp[i-1][1]. If the top of the
previous tower is connected, we can either extend it up by 1 or start a new
connected block. We can also start a new connected block on top of a non-
connected layer. Therefore, dp[i][1] = dp[i-1][1] * 2 + dp[i-1][0].

Use the image shown here (https://cses.fi/problemset/task/2413/) to visualize
the blocks.

*/

#include <iostream>

const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long dp[N][2];
    dp[1][0] = dp[1][1] = 1;
    for (int i = 2; i < N; ++i) {
        dp[i][0] = (dp[i - 1][0] * 4 + dp[i - 1][1]) % MOD;
        dp[i][1] = (dp[i - 1][1] * 2 + dp[i - 1][0]) % MOD;
    }
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::cout << ((dp[n][0] + dp[n][1]) % MOD) << '\n';
    }
}
