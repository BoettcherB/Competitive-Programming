#include <iostream>

const int N = 2e5 + 10;
const int MOD = 998244353;

class SegTree {
    int n;
    long long tree[4 * N];
    long long sumA[4 * N], sumB[4 * N];
    long long lazyA[4 * N], lazyB[4 * N];

    void build(int cur, int tl, int tr, int A[N], int B[N]) {
        if (tl == tr) {
            tree[cur] = (long long) A[tl] * B[tl] % MOD;
            sumA[cur] = A[tl] % MOD;
            sumB[cur] = B[tl] % MOD;
        } else {
            int mid = (tl + tr) / 2;
            build(cur * 2, tl, mid, A, B);
            build(cur * 2 + 1, mid + 1, tr, A, B);
            tree[cur] = (tree[cur * 2] + tree[cur * 2 + 1]) % MOD;
            sumA[cur] = (sumA[cur * 2] + sumA[cur * 2 + 1]) % MOD;
            sumB[cur] = (sumB[cur * 2] + sumB[cur * 2 + 1]) % MOD;
        }
        lazyA[cur] = lazyB[cur] = 0;
    }

    void propagate(int cur, int tl, int tr) {
        if (lazyA[cur] == 0 && lazyB[cur] == 0)
            return;
        tree[cur] = (tree[cur] + lazyA[cur] * sumB[cur]) % MOD;
        sumA[cur] = (sumA[cur] + lazyA[cur] * (1LL + tr - tl)) % MOD;
        tree[cur] = (tree[cur] + lazyB[cur] * sumA[cur]) % MOD;
        sumB[cur] = (sumB[cur] + lazyB[cur] * (1LL + tr - tl)) % MOD;
        if (tl != tr) {
            lazyA[cur * 2] = (lazyA[cur * 2] + lazyA[cur]) % MOD;
            lazyB[cur * 2] = (lazyB[cur * 2] + lazyB[cur]) % MOD;
            lazyA[cur * 2 + 1] = (lazyA[cur * 2 + 1] + lazyA[cur]) % MOD;
            lazyB[cur * 2 + 1] = (lazyB[cur * 2 + 1] + lazyB[cur]) % MOD;
        }
        lazyA[cur] = lazyB[cur] = 0;
    }

    void update(int cur, int tl, int tr, int ql, int qr, int val, bool A) {
        propagate(cur, tl, tr);
        if (ql <= tl && tr <= qr) {
            if (A) lazyA[cur] = (lazyA[cur] + val) % MOD;
            else   lazyB[cur] = (lazyB[cur] + val) % MOD;
            propagate(cur, tl, tr);
            return;
        }
        if (tl > qr || tr < ql)
            return;
        int mid = (tl + tr) / 2;
        update(cur * 2, tl, mid, ql, qr, val, A);
        update(cur * 2 + 1, mid + 1, tr, ql, qr, val, A);
        tree[cur] = (tree[cur * 2] + tree[cur * 2 + 1]) % MOD;
        sumA[cur] = (sumA[cur * 2] + sumA[cur * 2 + 1]) % MOD;
        sumB[cur] = (sumB[cur * 2] + sumB[cur * 2 + 1]) % MOD;
    }

    long long query(int cur, int tl, int tr, int ql, int qr) {
        propagate(cur, tl, tr);
        if (ql <= tl && tr <= qr)
            return tree[cur];
        if (tl > qr || tr < ql)
            return 0;
        int mid = (tl + tr) / 2;
        long long q1 = query(cur * 2, tl, mid, ql, qr);
        long long q2 = query(cur * 2 + 1, mid + 1, tr, ql, qr);
        return (q1 + q2) % MOD;
    }

public:
    SegTree(int n, int A[N], int B[N]) : n{ n } {
        build(1, 0, n - 1, A, B);
    }

    void update(int ql, int qr, int val, bool A) {
        if (ql > qr) return;
        update(1, 0, n - 1, ql - 1, qr - 1, val, A);
    }

    long long query(int ql, int qr) {
        if (ql > qr) return 0;
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
