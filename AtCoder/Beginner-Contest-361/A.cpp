#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k, x;
    std::cin >> n >> k >> x;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    a.insert(a.begin() + k, x);
    for (int i = 0; i <= n; ++i) {
        std::cout << a[i] << " \n"[i == n];
    }
}
