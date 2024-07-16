#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k, n, w, total = 0;
    std::cin >> k >> n >> w;
    for (int i = 1; i <= w; ++i) {
        total += i * k;
    }
    std::cout << std::max(0, total - n) << '\n';
}
