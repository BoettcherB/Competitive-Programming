#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long powers[64] = { 1 };
    for (int i = 1; i < 64; ++i) {
        powers[i] = powers[i - 1] << 1;
    }
    int T, n;
    std::cin >> T;
    while (T--) {
        long long n, i = 0, res = 0;
        std::cin >> n;
        while (powers[i] <= n) {
            res -= 2* powers[i++];
        }
        std::cout << res + n * (n + 1) / 2 << '\n';
    }
}
