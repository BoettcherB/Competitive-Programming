#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    long long dx = std::abs(x2 - x1), dy = std::abs(y2 - y1);
    long long res = dy;
    if (dy < dx) {
        dx -= dy;
        bool left = x1 % 2 == y1 % 2;
        if ((x1 < x2 && left) || (x1 > x2 && !left))
            res += dx / 2;
        else
            res += (dx + 1) / 2;
    }
    std::cout << res << '\n';
}
