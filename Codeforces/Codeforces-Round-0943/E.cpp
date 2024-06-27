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
        std::vector<std::pair<int, int>> cells = {
            {1, 1}, {n, n}, {1, 2}, {n, 2}, {1, 4}, 
        };
        std::pair<int, int> c1 = {n, n - 2}, c2 = {n - 2, 2};
        for (int i = 0; i < n / 2; ++i) {
            cells.push_back(c1);
            cells.push_back(c2);
            c1.second -= 2;
            c2.first -= 2;
        }
        for (int i = 0; i < n; ++i) {
            std::cout << cells[i].first << ' ' << cells[i].second << '\n';
        }
    }
}
