#include <iostream>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long h, p = 1, cnt = 1;
    std::cin >> h;
    while (p <= h) {
        p += std::pow(2, cnt++);
    }
    std::cout << cnt << '\n';
}
