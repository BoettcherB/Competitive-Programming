#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            std::cin >> x;
            a[j] -= x;
        }
    }
    auto isPos = [](int v) { return v > 0; };
    std::cout << (std::any_of(a.begin(), a.end(), isPos) ? "No\n" : "Yes\n");
}
