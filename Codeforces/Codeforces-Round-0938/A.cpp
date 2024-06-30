#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        std::cout << std::min(a * n, (n / 2) * b + (n % 2) * a) << '\n';
    }
}
