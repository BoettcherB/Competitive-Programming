/*

You have n apples, each with its own weight w_i. Your task is to divide the
apples into 2 groups so that the difference in weights of the groups is
minimal. Print the minimum possible difference in weights.

Constraints:
    1 <= n <= 20
    1 <= w_i <= 1,000,000,000

Example Input:
5
3 2 7 4 1

Example Output:
1

We can use brute force to try all 2^n groupings of apples to find the one with
the smallest difference. A recursive algorithm works well here. For every apple
try placing it in the first group, then in the second group. When all apples
have been placed in a group, find the difference between the groups.

*/

#include <iostream>

const int N = 21;
int n, arr[N];
long long res = 1e18;

void rec(int cur, long long g1, long long g2) {
    if (cur == n) {
        res = std::min(res, std::abs(g1 - g2));
        return;
    }
    rec(cur + 1, g1 + arr[cur], g2);
    rec(cur + 1, g1, g2 + arr[cur]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    rec(0, 0, 0);
    std::cout << res << '\n';
}
