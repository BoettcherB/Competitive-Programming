#include <iostream>
#include <cstring>

const int N = 31;
const int K = 51;
int cost[N][N][K];

int find_cost(int n, int m, int k) {
    if (cost[n][m][k] != -1) {
        return cost[n][m][k];
    }
    if (k == n * m || k == 0) {
        cost[n][m][k] = cost[m][n][k] = 0;
        return 0;
    }
    int min_cost = 2e9;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j <= i * m && k - j <= (n - i) * m) {
                int c = find_cost(i, m, j) + find_cost(n - i, m, k - j);
                min_cost = std::min(min_cost, c + m * m);
            }
        }
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j <= n * i && k - j <= n * (m - i)) {
                int c = find_cost(n, i, j) + find_cost(n, m - i, k - j);
                min_cost = std::min(min_cost, c + n * n);
            }
        }
    }
    cost[n][m][k] = cost[m][n][k] = min_cost;
    return min_cost;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::memset(cost, -1, N * N * K * 4);
    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        find_cost(n, m, k);
        std::cout << cost[n][m][k] << '\n';
    }
}
