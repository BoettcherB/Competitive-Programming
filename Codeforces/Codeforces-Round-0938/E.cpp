#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n;
        std::string str;
        std::cin >> n >> str;
        for (int k = n; k >= 1; --k) {
            std::string cur = str;
            int flips = 0;
            for (int i = 0; i <= n; ++i) {
                if (i - k >= 0 && cur[i - k] == '0') {
                    --flips;
                    cur[i - k] = '1';
                }
                if (flips % 2 == 1)
                    cur[i] = cur[i] == '0' ? '1' : '0';
                if (i <= n - k && cur[i] == '0')
                    ++flips;
            }
            bool ok = true;
            for (int i = n - k + 1; i < n; ++i) {
                if (cur[i] != cur[i - 1]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                std::cout << k << '\n';
                break;
            }
        }
    }
}
