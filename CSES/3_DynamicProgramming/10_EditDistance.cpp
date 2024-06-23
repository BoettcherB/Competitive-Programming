/*

CSES: Dynamic Programming: Edit Distance

You are given two strings whose lengths are a and b, and whose characters are
between A-Z. Find the edit distance between the strings (the minimum number of
operations needed to transform one of the strings into the other). A single
operation can either be adding a character, removing a character, or replacing
a character.

Constraints:
    1 <= n, m <= 5000

Example Input:
LOVE
MOVIE

Example Output:
2

Let dp[i][j] be the minimum number of operations needed to transform one string
into the other if we are only considering the first i characters of a and the
first j characters of b. Consider the substrings a[0..i] and b[0..j]. If these
substrings end in the same character, then that character will not add to the
edit distance. Therefore, dp[i][j] = dp[i - 1][j - 1] in this case. If we are
going to add a character to a, then dp[i][j] = dp[i - 1][j] + 1. If we are
going to remove a character from a, then dp[i][j] = dp[i][j - 1] + 1. If we
are going to replace a character, then dp[i][j] = dp[i-1][j-1] + 1. Take the
minimum of these.

Recurrence:
    dp[i][j] = dp[i - 1][j - 1] if a[i] == b[j]
    otherwise, dp[i][j] = 1 + min(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j])

*/

#include <iostream>
#include <string>

const int N = 5010;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string a, b;
    std::cin >> a >> b;
    int n = a.length(), m = b.length(), dp[N][N];
    for (int i = 0; i < N; ++i) {
        dp[0][i] = dp[i][0] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]) + 1;
            }
        }
    }
    std::cout << dp[n][m] << '\n';
}
