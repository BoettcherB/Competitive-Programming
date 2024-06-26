#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long x, y, k;
        std::cin >> x >> y >> k;
        while (x != 1 && k > 0) {
            long long nextMultiple = x / y * y + y;
            long long diff = std::min(k, nextMultiple - x);
            x += diff;
            k -= diff;
            while (x % y == 0) x /= y;
        }
        std::cout << (x + k % (y - 1)) << '\n';
    }
}
