#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> keys(m);
    std::vector<bool> open(m);
    for (int i = 0; i < m; ++i) {
        int c;
        std::cin >> c;
        keys[i] = std::vector<int>(c);
        for (int j = 0; j < c; ++j) {
            std::cin >> keys[i][j];
            --keys[i][j];
        }
        char r;
        std::cin >> r;
        open[i] = (r == 'o');
    }
    int res = 0;
    for (int real = 0; real < (1 << n); ++real) {
        bool ok = true;
        for (int i = 0; i < m; ++i) {
            int count = 0;
            for (const auto& key : keys[i]) {
                count += (real & (1 << key)) != 0;
            }
            if ((count >= k && !open[i]) || (count < k && open[i])) {
                ok = false;
                break;
            }
        }
        res += ok;
    }
    std::cout << res << '\n';
}
