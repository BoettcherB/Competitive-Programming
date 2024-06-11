#include <iostream>

const int N = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k, heights[N], dp[N] = { 0 };
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }
    for (int i = 1; i < n; ++i) {
        dp[i] = 2e9;
        for (int j = i - 1; j >= 0 && j >= i - k; --j) {
            dp[i] = std::min(dp[i], dp[j] + std::abs(heights[i] - heights[j]));
        }
    }
    std::cout << dp[n - 1] << '\n';
}
