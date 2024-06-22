#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> nums(n + m);
    std::set<int> a;
    for (int i = 0; i < n + m; ++i) {
        std::cin >> nums[i];
        if (i < n)
            a.insert(nums[i]);
    }
    std::sort(nums.begin(), nums.end());
    for (int i = 1; i < n + m; ++i) {
        if (a.count(nums[i]) && a.count(nums[i - 1])) {
            std::cout << "Yes" << '\n';
            return 0;
        }
    }
    std::cout << "No" << '\n';
}
