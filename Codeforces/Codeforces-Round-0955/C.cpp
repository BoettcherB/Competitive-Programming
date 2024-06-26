#include <iostream>
#include <vector>     
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, l, r;
        std::cin >> n >> l >> r;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        long long sum = 0, res = 0;
        std::list<int> list;
        for (int i = 0; i < n; ++i) {
            if (sum < l) {
                list.push_back(a[i]);
                sum += a[i];
            }
            while (sum > r) {
                sum -= list.front();
                list.pop_front();
            }
            if (l <= sum && sum <= r) {
                ++res;
                sum = 0;
                list.clear();
            }
        }
        std::cout << res << '\n';
    }
}
