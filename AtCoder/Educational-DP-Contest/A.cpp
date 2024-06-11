#include <iostream>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, heights[N], dp[N] = { 0 };
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }
    dp[1] = std::abs(heights[1] - heights[0]);
    for (int i = 2; i < n; ++i) {
        int s1 = std::abs(heights[i] - heights[i - 1]);
        int s2 = std::abs(heights[i] - heights[i - 2]);
        dp[i] = std::min(dp[i - 1] + s1, dp[i - 2] + s2);
    }
    std::cout << dp[n - 1] << '\n';
}
