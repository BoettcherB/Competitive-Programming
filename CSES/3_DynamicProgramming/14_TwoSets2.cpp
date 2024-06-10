/*

You are given an integer n. Your task is to count the number of ways that the
numbers from 1 to n can be divided into 2 sets of equal sum. Print the answer
mod 1e9 + 7.

Constraints:
    1 <= n <= 500

Example Input:
7

Example Output:
4

We can think of this problem as 'find the number of ways to 

First of all, the total sum S of all integers from 1 to n might be odd. We can
immediately print 0 if S is odd. This problem can be solved very similar to an
0-1 knapsack problem. Here, the items are the integers [1, 2, ..., n], and the
weights are the values of each integer (we are not concerned about the profit
of each item). Let dp[i][j] be the number of ways we can create the sum j using
only the first i numbers. The maximum sum we will try to create is S/2, since
we are trying to find the number of ways to create S/2 from the numbers 1-n. We
can initially say that dp[0][0] = 1 (there is one way to create the sum 0: by
using 0 numbers). To find dp[i][j], we can either use the i'th number of not.
If we do not use it, we can create the sum j in the same number of ways that we
created j while only considering the first i-1 values. In this case, dp[i][j] =
dp[i - 1][j]. If we do use the i'th number, we are only allowed to create the
sum j-i with the first i-1 values. In this case, dp[i][j] = dp[i - 1][j - i].
dp[i][j] is the sum of these 2 cases.

If we could use unbounded integers, the result would be dp[n][S/2] / 2 (we find
how many ways to create the sum S/2 with all n integers, then divide the result
by 2 because we are counting each half of S separately). However, since we are
trying to find the answer mod 1e9+7, we cannot divide by 2 (division does not
work with mod). Fortunately, dp[n][S/2] / 2 is equal to dp[n - 1][S/2]. This is
because, for each of the number of ways to divide up the n integers, exactly
half of them must use the integer n (remember, we either use an integer in
the sum or not).

*/

#include <iostream>

const int N = 510;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n, dp[N][N * N / 4] = { 1 };
    std::cin >> n;
    long long sum = n * (n + 1) / 2;
    if (sum % 2 == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= sum / 2; ++j) {
            dp[i][j] = dp[i - 1][j] + (j >= i ? dp[i - 1][j - i] : 0);
            dp[i][j] %= MOD;
        }
    }
    std::cout << dp[n - 1][sum / 2] << '\n';
}
