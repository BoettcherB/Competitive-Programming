/*

You have n apples, each with its own weight w_i. Your task is to divide the
apples into 2 groups so that the difference in weights of the groups is
minimal. Print the minimum possible difference in weights.

Constraints:
 - 1 <= n <= 20
 - 1 <= w_i <= 1,000,000,000

Example Input:
5
3 2 7 4 1

Example Output:
1

We can use brute force to try all 2^n groupings of apples to find the one with
the smallest difference. A recursive algorithm works well here. For every apple
try placing it in the first group, then in the second group, and return the
best result out of the two.

*/

#include <iostream>

const int N = 25;
int n, weights[N];

long long solve(int index, long long sum1, long long sum2) {
    if (index >= n)
        return std::abs(sum1 - sum2);
    return std::min(solve(index + 1, sum1 + weights[index], sum2),
                    solve(index + 1, sum1, sum2 + weights[index]));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    std::cout << solve(0, 0, 0) << std::endl;
}
