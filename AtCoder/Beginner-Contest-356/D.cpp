#include <iostream>

const int MOD = 998244353;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n, m, res = 0, pow2 = 2;
    std::cin >> n >> m;
    for (int i = 0; i < 60; ++i) {
        if (m & (1LL << i)) {
            long long power = (n + 1) / pow2 * pow2;
            long long rem = (n + 1) - power;
            res = (res + power / 2) % MOD;
            res = (res + std::max(0LL, rem - pow2 / 2)) % MOD;
        }
        pow2 *= 2;
    }
    std::cout << res << '\n';
}
