/*

CSES: Graph Algorithms: Hamiltonian Flights

You are given a directed graph with n vertices and m edges. Your task is to
count the number of ways to travel from vertex 1 to vertex n such that you
visit each vertex exactly once.

Constraints:
    2 <= n <= 20
    1 <= m <= n^2
    1 <= u, v <= n

Example Input:
4 6
1 2
1 3
2 3
3 2
2 4
3 4

Example Output:
2

This problem can be solved using bit DP. We can encode a 'state' of the graph
in an integer mask where the i'th bit in mask is 1 if the i'th vertex has been
visited. Using this we can create a dp array where dp[mask][i] is the number of
ways to travel from vertex 1 to vertex i if we have visited all the vertices in
mask. Loop through all masks and all vertices. For each mask/vertex pair (mask,
u), check all the edges (u, v) going out from the vertex u. The recurrence is
dp[mask + (1 << v)][v] += dp[mask][u].

*/

#include <iostream>
#include <vector>

const int N = 20;
const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    long long dp[1 << N][N] = { 0 };
    std::vector<std::vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }
    dp[1][0] = 1;
    for (int i = 1; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[i][j] == 0) continue;
            for (int adj : g[j]) {
                if (i & (1 << adj)) continue;
                dp[i + (1 << adj)][adj] += dp[i][j];
                dp[i + (1 << adj)][adj] %= MOD;
            }
        }
    }
    std::cout << dp[(1 << n) - 1][n - 1] << '\n';
}
