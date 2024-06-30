#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, res = 0;
    std::cin >> n;
    std::vector<int> prev(n + 1);
    for (int i = 1; i <= 2 * n; ++i) {
        int a;
        std::cin >> a;
        if (prev[a] == 0)
            prev[a] = i;
        else
            res += (i - prev[a] == 2);
    }
    std::cout << res << '\n';
}
