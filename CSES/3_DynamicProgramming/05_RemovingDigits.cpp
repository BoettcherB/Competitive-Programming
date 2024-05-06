/*

You are given a number n. In each step, you may subtract one of the digits from
that number (ex: for n = 27, you can either subtract 2 or 7 to get either 25 or
20). Print the minimum number of steps needed to reach 0.

Constraints:
    1 <= n <= 1,000,000

Example Input:
27

Example Output:
5

Start with dp[0] = 0 and dp[i] = infinity for all 1 <= i <= n. For every i,
loop through all digits d of i, subtract the digit from i, and find out how
many steps it takes to reach the number i - d (dp[i - d]). The number of steps
needed to reach i is dp[i - d] + 1. Do this for all digits of i and take the
minimum.

Recurrence: for every digit d of i, dp[i] = min(dp[i], dp[i - d] + 1)

*/

#include <iostream>

const int N = 1e6 + 10;
const int INF = 2e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, dp[N];
    std::cin >> n;
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = INF;
        int num = i;
        while (num > 0) {
            int digit = num % 10;
            dp[i] = std::min(dp[i], dp[i - digit] + 1);
            num /= 10;
        }
    }
    std::cout << dp[n] << '\n';
}
