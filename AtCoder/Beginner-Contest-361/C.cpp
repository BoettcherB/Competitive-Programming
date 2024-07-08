#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::sort(arr.begin(), arr.end());
    long long res = 3e18;
    for (int i = 0; i <= k; ++i) {
        res = std::min(res, arr[n - k - 1 + i] - arr[i]);
    }
    std::cout << res << '\n';
}
