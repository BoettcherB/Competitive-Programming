#include <iostream>
#include <string>

const int MOD = 998244353;

struct mint {
    long long v;
    mint(long long val = 0) { v = val % MOD + (val < 0) * MOD; }
    mint& operator+=(const mint o) { if ((v += o.v) > MOD) v -= MOD; return *this; }
    mint& operator-=(const mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(const mint o) { v = v * o.v % MOD; return *this; }
    mint& operator/=(const mint o) { return *this *= mpow(o, MOD - 2); }
    mint operator+(const mint o) const { return mint(*this) += o; }
    mint operator-(const mint o) const { return mint(*this) -= o; }
    mint operator*(const mint o) const { return mint(*this) *= o; }
    mint operator/(const mint o) const { return mint(*this) /= o; }
    friend mint mpow(mint a, long long b) {
        mint res = 1; while (b) { if (b & 1) res *= a; a *= a; b >>= 1; }
        return res;
    }
    operator long long() const { return v; }
    friend std::ostream& operator<<(std::ostream& os, const mint& m) {
        return os << m.v;
    }
    friend std::istream& operator>>(std::istream& is, mint& m) {
        long long val; std::cin >> val; m = mint(val); return is;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    mint k = std::to_string(n).length();
    mint k10 = mpow(10, k);
    mint res = mint(n) * (mpow(k10, n) - mint(1)) / (mpow(10, k) - mint(1));
    std::cout << res << std::endl;
}

/*

Solution without mint:

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
    long long n;
    std::cin >> n;
    int k = std::to_string(n).length();
    long long k10 = binexp(10, k, MOD);
    long long term1 = n % MOD * (binexp(k10, n, MOD) - 1) % MOD;
    long long term2 = binexp(k10 - 1, MOD - 2, MOD);
    std::cout << term1 * term2 % MOD << '\n';
}

*/
