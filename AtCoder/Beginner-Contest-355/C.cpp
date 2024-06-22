#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, t;
    std::cin >> n >> t;
    std::vector<int> row(n + 1, n), col(n + 1, n);
    int diag1 = n, diag2 = n;
    for (int turn = 1; turn <= t; ++turn) {
        int x;
        std::cin >> x;
        int j = x % n == 0 ? n : x % n;
        int i = (x - j) / n + 1;
        --row[i]; --col[j];
        if (i == j) --diag1;
        if (i == n - j + 1) --diag2;
        if (row[i] <= 0 || col[j] <= 0 || diag1 <= 0 || diag2 <= 0) {
            std::cout << turn << '\n';
            return 0;
        }
    }
    std::cout << -1 << '\n';
}
