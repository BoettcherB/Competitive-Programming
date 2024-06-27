#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, k, pb, ps;
        std::cin >> n >> k >> pb >> ps;
        std::vector<long long> p(n + 1), a(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> p[i];
        }
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }
        long long res1 = 0, res2 = 0, sum1 = 0, sum2 = 0;
        for (int i = 0; i < n && k > 0; ++i) {
            sum1 += a[pb];
            sum2 += a[ps];
            --k;
            res1 = std::max(res1, sum1 + a[pb] * k);
            res2 = std::max(res2, sum2 + a[ps] * k);
            pb = p[pb];
            ps = p[ps];
        }
        if (res1 > res2)
            std::cout << "Bodya" << '\n';
        else if (res2 > res1)
            std::cout << "Sasha" << '\n';
        else
            std::cout << "Draw" << '\n';
    }
}
