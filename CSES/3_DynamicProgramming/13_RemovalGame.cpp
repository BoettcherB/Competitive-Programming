/*

CSES: Dynamic Programming: Removal Game

There is a list of n numbers [x0, x1, ..., xn]. In a 2-player game, each player
takes turns removing either the first or last number from the list and adding
that number to their score. Both players try to maximize their score. What is
the maximum possible score for the first player if both players play optimally?

Constraints:
    1 <= n <= 5000
    -1,000,000,000 <= x <= 1,000,000,000

Example Input:
4
4 5 1 3

Example Output:
8

Let dp[i][j] be the best possible score for the first player when only the
indexes i-j remain in the list. When considering the list between i-j, if it is
the first player's turn then that player can either choose the number at index
i or the number at index j. If the player chooses i, then their score will be
arr[i] + dp[i+1][j]. If they choose j their score will be arr[j] + dp[i][j-1].
If it is player 2's turn, then player 2 will choose either arr[i] or arr[j],
whichever results in a lower score for player 1. The best score for player 1
when it is player 2's turn is the minimum of dp[i+1][j] and dp[i][j-1]. This
problem is most-easily solved with a top-down recursion method. 

*/

#include <iostream>

const int N = 5010;
const long long INF = 1e18;
int n, arr[N];
long long dp[N][N];

long long solve(int l, int r) {
    if (l > r)
        return 0;
    if (dp[l][r] == INF) {
        if ((r - l + 1) % 2 == n % 2)
            dp[l][r] = std::max(arr[l] + solve(l + 1, r),
                                arr[r] + solve(l, r - 1));
        else
            dp[l][r] = std::min(solve(l + 1, r), solve(l, r - 1));
    }
    return dp[l][r];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        for (int j = 0; j < n; ++j) {
            dp[i][j] = INF;
        }
    }
    std::cout << solve(0, n - 1) << '\n';
}
