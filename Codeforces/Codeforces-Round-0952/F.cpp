#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long h, n;
        std::cin >> h >> n;
        std::vector<long long> attack(n), cooldown(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> attack[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> cooldown[i];
        }
        long long l = 0, r = (long long) 1e12; // (l, r]
        while (l + 1 < r) {
            long long mid = (l + r) / 2;
            long long health = h;
            for (int i = 0; i < n; ++i) {
                health -= attack[i] + ((mid - 1) / cooldown[i]) * attack[i];
                if (health <= 0) break;
            }
            (health <= 0 ? r : l) = mid;
        }
        std::cout << r << '\n';
    }
}
