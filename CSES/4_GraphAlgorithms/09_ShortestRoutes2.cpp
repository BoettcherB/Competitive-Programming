/*

CSES: Graph Algorithms: Shortest Routes 2

You are given a weighted, undirected graph with n vertices and m edges. Each
edge (u, v) has a cost c. You are given q queries between 2 vertices u and v
and your task is to find, for each query, the length of the shortest path from
u to v. If there is no path from u to v, print -1.

Constraints:
    1 <= n <= 500
    1 <= m <= n^2
    1 <= q <= 100,000
    1 <= u, v <= n
    1 <= c <= 1,000,000,000

Example Input:
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2

Example Output:
5
5
8
-1
3

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

This problem can be solved using the Floyd-Warshall all-pairs shortest paths
algorithm. Let dp[i][j] be the length of the shortest path from i to j.
Initially, dp[i][j] = c if there is an edge with cost c from i to j, 0 if i ==
j, and infinity if there is no edge from i to j. For every pair of vertices (i,
j), we can treat vertex k as an intermediary and try to find the length of the
path from i to k, then from k to j. The runtime is O(n^3).

Recurrence: dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])

*/

#include <iostream>
#include <vector>

typedef std::vector<long long> vecLL;
const long long INF = 3e18;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<vecLL> dp(n + 1, vecLL(n + 1, INF));
    for (int i = 0; i < m; ++i) {
        long long u, v, c;
        std::cin >> u >> v >> c;
        dp[u][v] = dp[v][u] = std::min(dp[u][v], c);
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << (dp[u][v] == INF ? -1 : dp[u][v]) << '\n';
    }
}
