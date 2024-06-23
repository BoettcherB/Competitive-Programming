/*

Problem Statement: https://codeforces.com/contest/1985/problem/G

To solve this problem, start by determining which numbers satisfy the condition
k * d(n) == d(k * n). We can do this by implementing d(n) and trying all values
of n from 0 to some upper bound (say, 10000). If we do this, we will see that
for a number to satisfy the condition, all digits of the number must be <= 9/k.

Intuitively, if all digits are <= 9/k and we multiply n * k, none of the digits
will overflow into the next digit. Therefore, the sum of the digits of n * k is
equal to k times the sum of the digits of n.

Now, the problem is this: Let count(l, r, k) be the number of numbers between
10^l and 10^r where all digits are <= 9/k. This range contains all numbers that
have d digits where l < d <= r. We can solve this by finding the answer for all
numbers that have up to r digits, and then subtracting the numbers that have up
to l digits (ie. count(l, r, k) = count(0, r, k) - count(0, l, k)). To find the
number of numbers with <= d digits that satisfy d[i] <= 9/k, we simply need to
take the number of possible values per digits (which is 9/k+1) to the d'th
power (because we are choosing from 9/k+1 values d times). Therefore, count(0,
r, k) = (9/k+1)^r and count(0, l, k) = (9/k+1)^l.

To find these values, we can use binary exponentiation which can solve a^b % m
in O(log(b)) time. Below, I am using a custom wrapper around a long long which
automatically applies mod and comes with a pow(a, b) function.

*/

#include <iostream>

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        mint l, r, k;
        std::cin >> l >> r >> k;
        std::cout << mpow(9 / k + 1, r) - mpow(9 / k + 1, l) << '\n';
    }
}
