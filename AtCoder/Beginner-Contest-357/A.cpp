#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, h, res = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> h;
        m -= h;
        res += (m >= 0);
    }
    std::cout << res << '\n';
}
