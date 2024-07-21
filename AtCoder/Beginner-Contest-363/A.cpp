#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int r;
    std::cin >> r;
    std::cout << 100 - r % 100 << '\n';
}
