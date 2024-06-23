#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long X, Y, Z, vol, res = 0;
        std::cin >> X >> Y >> Z >> vol;
        for (int x = 1; x <= X; ++x) {
            if (vol % x != 0) continue;
            long long yz = vol / x;
            for (int y = 1; y <= Y; ++y) {
                if (yz % y != 0) continue;
                long long z = yz / y;
                if (z > Z) continue;
                res = std::max(res, (X - x + 1) * (Y - y + 1) * (Z - z + 1));
            }
        }
        std::cout << res << '\n';
    }
}
