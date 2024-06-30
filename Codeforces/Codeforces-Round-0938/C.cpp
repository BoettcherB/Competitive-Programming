#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long n, k;
        std::cin >> n >> k;
        std::vector<long long> ships(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> ships[i];
        }
        int p1 = 0, p2 = n - 1, res = 0;
        bool begin = true;
        while (k > 0 && p1 <= p2) {
            if (p1 == p2) {
                res += ships[p1] <= k;
                break;
            }
            if (!begin) {
                --ships[p2];
                if (ships[p2] == 0) {
                    ++res;
                    --p2;
                }
                --k;
                begin = true;
            } else if (ships[p1] > ships[p2]) {
                k -= 2 * ships[p2];
                if (k < 0) break;
                ships[p1] -= ships[p2--];
                ++res;
            } else {
                k -= 2 * ships[p1] - 1;
                if (k < 0) break;
                ships[p2] -= ships[p1++] - 1;
                ++res;
                begin = false;
            }
        }
        std::cout << res << '\n';
    }
}
