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
        int bestX, bestSum = 0;
        for (int x = 2; x <= n; ++x) {
            int cur = x, sum = 0;
            while (cur <= n) {
                sum += cur;
                cur += x;
            }
            if (sum > bestSum) {
                bestSum = sum;
                bestX = x;
            }
        }
        std::cout << bestX << '\n';
    }
}
