#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n;
        std::cin >> n;
        long long x, sum = 0, max = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> x;
            sum += x;
            max = std::max(max, x);
            res += (sum - max == max);
        }
        std::cout << res << '\n';
    }
}
