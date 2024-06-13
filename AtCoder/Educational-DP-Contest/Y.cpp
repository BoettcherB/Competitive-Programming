#include <iostream>
#include <vector>
#include <algorithm>

const int MOD = 1e9 + 7;

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

struct Wall {
    int r, c;
    bool operator<(const Wall& other) const {
        return c == other.c ? r < other.r : c < other.c;
    }
};

const int MAX_FACT = 2e5 + 10;
std::vector<mint> fact(MAX_FACT), fact_inv(MAX_FACT);
mint nCr(int n, int r) {
    if (r == 0) return 1;
    return fact[n] * fact_inv[n - r] * fact_inv[r];
}

mint paths(const Wall& w1, const Wall& w2 = {0, 0}) {
    int dr = std::abs(w1.r - w2.r);
    int dc = std::abs(w1.c - w2.c);
    return nCr(dr + dc, dc);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    fact[0] = fact_inv[0] = 1;
    for (int i = 1; i < MAX_FACT; ++i) {
        fact[i] = fact[i - 1] * (mint) i;
        fact_inv[i] = (mint) 1 / fact[i];
    }

    int h, w, n;
    std::cin >> h >> w >> n;
    --h; --w;
    std::vector<Wall> walls(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> walls[i].r >> walls[i].c;
        --walls[i].r; --walls[i].c;
    }
    walls.push_back({ h, w });
    std::sort(walls.begin(), walls.end());
    std::vector<mint> dp(n + 1);
    for (int i = 0; i <= n; ++i) {
        dp[i] = paths(walls[i]);
        for (int j = 0; j < i; ++j) {
            if (walls[j].r <= walls[i].r && walls[j].c <= walls[i].c) {
                dp[i] -= dp[j] * paths(walls[i], walls[j]);
            }
        }
    }
    std::cout << dp[n] << '\n';
}
