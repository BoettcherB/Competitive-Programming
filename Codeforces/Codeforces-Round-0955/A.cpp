#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if ((x1 > y1 && x2 < y2) || (x1 < y1 && x2 > y2))
            std::cout << "NO" << '\n';
        else
            std::cout << "YES" << '\n';
    }
}
