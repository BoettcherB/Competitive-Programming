#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long n, c;
        std::cin >> n >> c;
        std::vector<long long> fans(n), prefix(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> fans[i];
        }
        fans[0] += c;
        prefix[0] = fans[0];
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] + fans[i];
        }
        int max = std::max_element(fans.begin(), fans.end()) - fans.begin();
        for (int i = 0; i < n; ++i) {
            int res = (i == max ? 0 : i + (fans[max] > prefix[i]));
            std::cout << res << " \n"[i == n - 1];
        }
    }
}
