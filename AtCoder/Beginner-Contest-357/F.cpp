#include <iostream>

const int N = 2e5 + 10;
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

class SegTree {
    int n;
    mint tree[4 * N];
    mint sumA[4 * N], sumB[4 * N];
    mint lazyA[4 * N], lazyB[4 * N];

    void build(int cur, int tl, int tr, int A[N], int B[N]) {
        if (tl == tr) {
            tree[cur] = mint(A[tl]) * mint(B[tl]);
            sumA[cur] = A[tl];
            sumB[cur] = B[tl];
        } else {
            int mid = (tl + tr) / 2;
            build(cur * 2, tl, mid, A, B);
            build(cur * 2 + 1, mid + 1, tr, A, B);
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
            sumA[cur] = sumA[cur * 2] + sumA[cur * 2 + 1];
            sumB[cur] = sumB[cur * 2] + sumB[cur * 2 + 1];
        }
        lazyA[cur] = lazyB[cur] = 0;
    }

    void propagate(int cur, int tl, int tr) {
        if (lazyA[cur] == 0 && lazyB[cur] == 0)
            return;
        tree[cur] += lazyA[cur] * sumB[cur];
        sumA[cur] += lazyA[cur] * mint(1 + tr - tl);
        tree[cur] += lazyB[cur] * sumA[cur];
        sumB[cur] += lazyB[cur] * mint(1 + tr - tl);
        if (tl != tr) {
            lazyA[cur * 2] += lazyA[cur];
            lazyB[cur * 2] += lazyB[cur];
            lazyA[cur * 2 + 1] += lazyA[cur];
            lazyB[cur * 2 + 1] += lazyB[cur];
        }
        lazyA[cur] = lazyB[cur] = 0;
    }

    void update(int cur, int tl, int tr, int ql, int qr, int val, bool A) {
        propagate(cur, tl, tr);
        if (ql <= tl && tr <= qr) {
            (A ? lazyA[cur] : lazyB[cur]) += val;
            propagate(cur, tl, tr);
            return;
        }
        if (tl > qr || tr < ql)
            return;
        int mid = (tl + tr) / 2;
        update(cur * 2, tl, mid, ql, qr, val, A);
        update(cur * 2 + 1, mid + 1, tr, ql, qr, val, A);
        tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        sumA[cur] = sumA[cur * 2] + sumA[cur * 2 + 1];
        sumB[cur] = sumB[cur * 2] + sumB[cur * 2 + 1];
    }

    mint query(int cur, int tl, int tr, int ql, int qr) {
        propagate(cur, tl, tr);
        if (ql <= tl && tr <= qr)
            return tree[cur];
        if (tl > qr || tr < ql)
            return 0;
        int mid = (tl + tr) / 2;
        return query(cur * 2, tl, mid, ql, qr)
            + query(cur * 2 + 1, mid + 1, tr, ql, qr);
    }

public:
    SegTree(int n, int A[N], int B[N]) : n{ n } {
        build(1, 0, n - 1, A, B);
    }

    void update(int ql, int qr, int val, bool A) {
        update(1, 0, n - 1, ql - 1, qr - 1, val, A);
    }

    mint query(int ql, int qr) {
        return query(1, 0, n - 1, ql - 1, qr - 1);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q, A[N], B[N];
    std::cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> B[i];
    }
    SegTree st(n, A, B);
    while (q--) {
        int t, l, r, x;
        std::cin >> t;
        if (t == 1 || t == 2) {
            std::cin >> l >> r >> x;
            st.update(l, r, x, t == 1);
        } else {
            std::cin >> l >> r;
            std::cout << st.query(l, r) << '\n';
        }
    }
}
