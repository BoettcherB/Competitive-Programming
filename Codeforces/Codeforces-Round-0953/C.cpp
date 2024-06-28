#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long n, k;
        std::cin >> n >> k;
        std::vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
        for (int i = 1; i <= n / 2; ++i) {
            long long index = std::min(k / 2 + i, n - i + 1);
            k -= (index - i) * 2;
            std::swap(p[i], p[index]);
        }
        if (k != 0)
            std::cout << "NO" << '\n';
        else {
            std::cout << "YES" << '\n';
            for (int i = 1; i <= n; ++i) {
                std::cout << p[i] << " \n"[i == n];
            }
        }
    }
}
