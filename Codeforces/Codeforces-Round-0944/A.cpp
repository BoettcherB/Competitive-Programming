#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int x, y;
        std::cin >> x >> y;
        std::cout << std::min(x, y) << ' ' << std::max(x, y) << '\n';
    }
}
