#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, l, r;
    std::cin >> n >> l >> r;
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        v[i] = i;
    }
    std::reverse(v.begin() + l, v.begin() + r + 1);
    for (int i = 1; i <= n; ++i) {
        std::cout << v[i] << " \n"[i == n];
    }
}
