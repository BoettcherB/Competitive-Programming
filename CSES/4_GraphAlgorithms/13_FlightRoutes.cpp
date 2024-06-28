/*

CSES: Graph Algorithms: Flight Routes

You are given a directed, weighted graph with n vertices and m edges. Each edge
(u, v) has a weight w. Your task is to find the k shortest routes from vertex 1
to vertex n. Each route can visit the same city multiple times. Print out the
lengths of the k shortest routes in sorted order.

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    1 <= w <= 1,000,000,000
    1 <= k <= 10
    There are at least k paths from vertex 1 to vertex n

Example Input:
4 6 3
1 2 1
1 3 3
2 3 2
2 4 6
3 2 8
3 4 1

Example Output:
4 4 7

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

This problem can be solved with Dijkstra's algorithm, though instead of storing
a single distance for each vertex, we need to store k distances: d[u][k] is the
length of the k'th best route from 1 to u. For each edge (u, v, w), only visit
vertex v if the length of the k'th best route (dist[v][k]) is greater than the
length current path to u + w.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

typedef std::vector<long long> vecLL;
const long long INF = 3e18;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    std::vector<vecLL> best(n + 1, vecLL(k, INF));
    std::priority_queue<std::pair<long long, int>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        long long pathCost = -pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (pathCost >= best[u][k - 1]) continue;
        best[u][k - 1] = pathCost;
        std::sort(best[u].begin(), best[u].end());
        for (const auto& adj : g[u]) {
            int v = adj.first, w = adj.second;
            if (pathCost + w < best[v][k - 1])
                pq.emplace(-pathCost - w, v);
        }
    }
    for (int i = 0; i < k; ++i) {
        std::cout << best[n][i] << " \n"[i == k - 1];
    }
}
