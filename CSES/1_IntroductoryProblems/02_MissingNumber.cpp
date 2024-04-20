#include <iostream>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    bool found[N] = { false };
    for (int i = 0; i < n - 1; ++i) {
        int x;
        std::cin >> x;
        found[x] = true;
    }
    for (int i = 1; i <= n; ++i) {
        if (!found[i]) {
            std::cout << i << '\n';
            break;
        }
    }
}
