#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> ranges(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> ranges[i].second >> ranges[i].first;
    }
    std::sort(ranges.begin(), ranges.end());
    long long res = 0;
    for (int i = 1; i < n; ++i) {
        std::pair<int, int> comp = { ranges[i].second, 0 };
        auto itr = std::lower_bound(ranges.begin(), ranges.begin() + i, comp);
        res += ranges.begin() + i - itr;
    }
    std::cout << res << '\n';
}
