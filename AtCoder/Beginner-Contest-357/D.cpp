#include <iostream>
#include <string>

const int MOD = 998244353;

long long binexp(long long a, long long b, long long mod) {
    a %= mod;
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    int k = std::to_string(n).length();
    long long k10 = binexp(10, k, MOD);
    long long term1 = n % MOD * (binexp(k10, n, MOD) - 1) % MOD;
    long long term2 = binexp(k10 - 1, MOD - 2, MOD);
    std::cout << term1 * term2 % MOD << '\n';
}
