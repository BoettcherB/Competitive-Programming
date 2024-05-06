/*

You are given an nxn grid of cells. Each cell is either empty ('.') or has a
trap ('*'). Find the number of paths from the top left to the top right,
without stepping on any traps, if you can only move down and to the right.

Constraints:
    1 <= n <= 1,000,000

Example Input:
4
....
.*..
...*
*...

Example Output:
3

Start by setting all dp[i][j] to 0. Then, set the initial cell (do[1][1]) to 1.
For every cell that is not a trap, add the number of paths to the cell above
and the cell to the left (if they are not traps). It is possible that the
starting and ending cells are traps, in which case the answer is 0.

Recurrence: dp[i][j] = dp[i - 1][j] + dp[i][j - 1]

*/

#include <iostream>
#include <string>

const int N = 1010;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    long long dp[N][N] = { 0 };
    for (int i = 1; i <= n; ++i) {
        std::string str;
        std::cin >> str;
        for (int j = 1; j <= n; ++j) {
            if (str[j - 1] == '*') {
                dp[i][j] = -1;
            }
        }
    }
    if (dp[1][1] == -1 || dp[n][n] == -1) {
        std::cout << 0 << '\n';
        return 0;
    }
    dp[1][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dp[i][j] == -1)
                continue;
            if (dp[i][j - 1] != -1)
                dp[i][j] += dp[i][j - 1];
            if (dp[i - 1][j] != -1)
                dp[i][j] += dp[i - 1][j];
            dp[i][j] %= MOD;
        }
    }
    std::cout << dp[n][n] << '\n';
}
