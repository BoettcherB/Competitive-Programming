/*

A book shop sells n books. Each book has a price h and a number of pages s. The
maximum amount of money you can spend is x. What is the maximum number of pages
you can buy?

Constraints:
    1 <= n <= 1000
    1 <= x <= 100,000
    1 <= h, s <= 1000

Example Input:
4 10
4 8 5 3
5 12 8 1

Example Output:
13

This is the classic 0-1 knapsack problem. Let dp[i][j] be the number of pages
we can buy if we only consider the first i books and can spend a maximum of j.
For every book, we can either buy it or not buy it. If we don't buy it, then
dp[i][j] = dp[i - 1][j] (ie. the same answer if we consider only the i-1 books
before the current book). If we buy the current book (which has a price of h
and s pages), then we can only spend j - h on the previous books. So dp[i][j]
= dp[i - 1][j - h] + s.

Recurrence: dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - h_i] + s_i).

*/

#include <iostream>

const int N = 1010;
const int X = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, price[N], pages[N], dp[N][X] = { 0 };
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        std::cin >> price[i];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> pages[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= price[i]) {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - price[i]] + pages[i]);
            }
        }
    }
    std::cout << dp[n][x] << '\n';
}
