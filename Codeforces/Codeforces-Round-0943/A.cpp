#include <iostream>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int x, max = 0, bestY = 0;
        std::cin >> x;
        for (int y = 1; y < x; ++y) {
            int val = gcd(x, y) + y;
            if (val > max) {
                max = val;
                bestY = y;
            }
        }
        std::cout << bestY << '\n';
    }
}
