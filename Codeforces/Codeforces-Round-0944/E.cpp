#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, k, q;
        std::cin >> n >> k >> q;
        std::vector<int> a(k + 1), b(k + 1);
        for (int i = 1; i <= k; ++i) {
            std::cin >> a[i];
        }
        for (int i = 1; i <= k; ++i) {
            std::cin >> b[i];
        }
        while (q--) {
            int d;
            std::cin >> d;
            int index = --std::upper_bound(a.begin(), a.end(), d) - a.begin();
            if (index == k)
                std::cout << b[k] << ' ';
            else {
                d -= a[index];
                long long dist = a[index + 1] - a[index];
                long long time = b[index + 1] - b[index];
                std::cout << (b[index] + time * d / dist) << ' ';
            }
        }
        std::cout << '\n';
    }
}
