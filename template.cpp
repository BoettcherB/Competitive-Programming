#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

template <class T> struct rge { T b, e; };
template <class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template <class T> auto dud(T* x) -> decltype(std::cerr << *x, 0);
template <class T> char dud(...);
struct debug {
    ~debug() { std::cerr << std::endl; }
    template <class T>
    typename std::enable_if<sizeof(dud<T>(0)) != 1, debug&>::type operator<<(T i) {
        std::cerr << std::boolalpha << i;
        return *this;
    }
    template <class T>
    typename std::enable_if<sizeof(dud<T>(0)) == 1, debug&>::type operator<<(T i) {
        return *this << range(std::begin(i), std::end(i));
    }
    template <class T1, class T2>
    debug& operator<<(std::pair<T1, T2> p) {
        return *this << "(" << p.first << ", " << p.second << ")";
    }
    template <class c> debug& operator<< (rge<c> d) {
        *this << "[";
        for (auto it = d.b; it != d.e; ++it)
            *this << ", " + 2 * (it == d.b) << *it;
        return *this << "]";
    }
};
#define RED_TXT "\033[31m"
#define RESET_TXT "\033[0m"
#ifdef DB_LOCAL
#define pprint(x) (debug() << RED_TXT << " [" << #x ": " << (x) << "] " << RESET_TXT)
#else
#define pprint(x)
#endif

const int MOD = 998244353;

struct mint {
    long long v;
    mint(long long val = 0) { v = val % MOD + (val < 0) * MOD; }
    mint& operator+=(const mint o) { if ((v += o.v) > MOD) v -= MOD; return *this; }
    mint& operator-=(const mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(const mint o) { v = v * o.v % MOD; return *this; }
    mint& operator/=(const mint o) { return *this *= mpow(o, MOD - 2); }
    mint operator+(const mint o) const { return mint(v) += o; }
    mint operator-(const mint o) const { return mint(v) -= o; }
    mint operator*(const mint o) const { return mint(v) *= o; }
    mint operator/(const mint o) const { return mint(v) /= o; }
    mint operator+(long long x) const { return mint(v + x); }
    mint operator-(long long x) const { return mint(v - x); }
    mint operator*(long long x) const { return mint(v * x); }
    mint operator/(long long x) const { return mint(v / x); }
    mint operator+(int x) const { return mint(v + x); }
    mint operator-(int x) const { return mint(v - x); }
    mint operator*(int x) const { return mint(v * x); }
    mint operator/(int x) const { return mint(v / x); }
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
        int n;
        std::cin >> n;
        
    }
}
