/*

CSES: Dynamic Programming: Money Sums

You have n coins, each with a value x. Your task is to find all the money sums
that can be made with these coins.

Constraints:
    1 <= n <= 100
    1 <= x <= 1000

Example Input:
4
4 2 5 2

Example Output:
9
2 4 5 6 7 8 9 11 13

Let dp[i][j] be true if we can create the sum j using the first i coins. Lets
say we are considering the i'th coin with a value x. Loop through all sums that
can be created with the previous i-1 coins (where dp[i-1][j] is true for any
j). If dp[i-1][j] is true, then dp[i][j] should also be true because we can
still create the sum j using the first i coins even if we don't use the i'th
coin. Also, dp[i][j + x] should be true because if we use the i'th coin then
we are able to create the sum j + x.

Recurrence: if dp[i-1][j] is true, then dp[i][j] and dp[i][j + x_i] are true

*/

#include <iostream>
#include <vector>

const int N = 110;
const int X = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    bool dp[N][X] = { true };
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        int coin;
        std::cin >> coin;
        for (int j = 0; j < X; ++j) {
            if (dp[i - 1][j]) {
                dp[i][j] = dp[i][j + coin] = true;
            }
        }
    }
    std::vector<int> sums;
    for (int j = 1; j < X; ++j) {
        if (dp[n][j]) {
            sums.push_back(j);
        }
    }
    std::cout << sums.size() << '\n';
    for (int s : sums) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
}
