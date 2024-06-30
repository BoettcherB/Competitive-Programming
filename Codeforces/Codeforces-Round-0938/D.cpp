#include <iostream>
#include <vector>

const int N = 1e6 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    std::vector<int> countA(N), countB(N);
    while (tc--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<int> a(n + 1), b(m + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }
        for (int i = 1; i <= m; ++i) {
            std::cin >> b[i];
            ++countB[b[i]];
        }
        int count = 0;
        for (int i = 0; i < m; ++i) {
            ++countA[a[i]];
            count += countB[a[i]] >= countA[a[i]];
        }
        int res = 0;
        for (int i = 0; i <= n - m; ++i) {
            int add = a[i + m], del = a[i];
            count -= countA[del] <= countB[del];
            --countA[del];
            ++countA[add];
            count += countA[add] <= countB[add];
            res += count >= k;
        }
        std::cout << res << '\n';
        for (int i = n - m + 1; i <= n; ++i) --countA[a[i]];
        for (int i = 1; i <= m; ++i) --countB[b[i]];
    }
}
