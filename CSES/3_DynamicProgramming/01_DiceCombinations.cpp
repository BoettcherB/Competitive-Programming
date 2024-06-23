/*

CSES: Dynamic Programming: Dice Combinations

Count the number of ways to construct n by throwing a dice 1 or more times.
Each dice roll results in a number between 1 and 6 inclusive. Print the answer
modulo 10^9 + 7.

Constraints:
    1 <= n <= 1,000,000

Example Input:
3

Example Output:
4

Let dp[n] be the number of ways to construct the number n with dice rolls. To
find dp[n], take the sum dp[n-1] + dp[n-2] + dp[n-3] + dp[n-4] + dp[n-5] +
dp[n-6]. This works because to construct n you can roll dice until you get n-1,
then roll a 1. You could also roll dice until you get n-2, and then roll a 2.
We have to be careful with this calculation when n <= 6 to factor in the lone
roll where the number on the dice equals n. We can account for this by setting
dp[0] = 1.

*/

#include <iostream>

const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    long long dp[N] = { 1 };
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i - j >= 0) {
                dp[i] += dp[i - j];
            }
        }
        dp[i] %= MOD;
    }
    std::cout << dp[n] << '\n';
}
