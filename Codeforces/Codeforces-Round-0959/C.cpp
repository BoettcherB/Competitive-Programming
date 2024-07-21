#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, x;
        std::cin >> n >> x;
        std::vector<int> arr(n + 1), dp(n + 3);
        for (int i = 1; i <= n; ++i) {
            std::cin >> arr[i];
        }
        int p = n + 1;
        long long sum = 0, res = 0;
        for (int i = n; i > 0; --i) {
            sum += arr[i];
            while (sum > x) {
                sum -= arr[--p];
            }
            dp[i] = p - i + dp[p + 1];
            res += dp[i];
        }
        std::cout << res << '\n';
    }
}
