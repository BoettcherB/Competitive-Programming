#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, m;
        std::string row;
        std::cin >> n >> m;
        std::pair<int, int> x = { -1, -1 }, y = { 2e9, 2e9 };
        for (int i = 0; i < n; ++i) {
            std::cin >> row;
            size_t pos = row.find('#');
            if (pos == std::string::npos)
                continue;
            if (x.first == -1)
                x = { i, pos, };
            y = std::min(y, { pos, i });
        }
        std::cout << y.second + 1 << ' ' << x.second + 1 << '\n';
    }
}
