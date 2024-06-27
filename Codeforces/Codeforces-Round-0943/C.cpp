#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n;
        std::cin >> n;
        std::vector<int> x(n), a(n);
        for (int i = 1; i < n; ++i) {
            std::cin >> x[i];
        }
        a[0] = x[1] + 1;
        for (int i = 1; i < n; ++i) {
            a[i] = x[i];
            if (i < n - 1 && a[i] <= x[i + 1])
                a[i] += a[i - 1] * ((x[i + 1] - a[i]) / a[i] + 1);
        }
        for (int i = 0; i < n; ++i) {
            std::cout << a[i] << " \n"[i == n - 1];
        }
    }
}
