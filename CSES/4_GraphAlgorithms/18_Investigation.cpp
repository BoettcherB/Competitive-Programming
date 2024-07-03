/*

CSES: Graph Algorithms: Investigation

You are given a weighted, directed graph with n vertices and m edges. Each edge
(u, v) has a weight w. Your task is to these values:
    1. What is the length of the shortest path from vertex 1 to vertex n?
    2. How many shortest paths are there from 1 to n?
    3. What is the minimum number of edges on any shortest path?
    4. What is the maximum number of edges on any shortest path?

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    1 <= w <= 1,000,000,000

Example Input:
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3

Example Output:
5 2 1 2

This problem can be solved with dijkstra's algorithm. For each vertex v, store
the length of the shortest path to v, the number of shortest paths to v, the
min/max edges on any shortest path to v, and whether v has been visited. After
visiting a vertex u, update these values for all vertices adjacent to u.

*/

#include <iostream>
#include <vector>
#include <queue>

const long long INF = 3e18;
const int MOD = 1e9 + 7;
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    std::vector<long long> cost(n + 1, INF), count(n + 1);
    std::vector<int> min(n + 1), max(n + 1), visited(n + 1);
    cost[1] = 0;
    count[1] = 1;
    std::priority_queue<std::pair<long long, int>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        long long pathCost = -cur.first;
        int u = cur.second;
        if (visited[u]) continue;
        visited[u] = true;
        for (const auto& adj : g[u]) {
            int v = adj.first, w = adj.second;
            if (pathCost + w < cost[v]) {
                cost[v] = pathCost + w;
                count[v] = count[u];
                min[v] = min[u] + 1;
                max[v] = max[u] + 1;
                pq.push({-cost[v], v});
            }
            else if (pathCost + w == cost[v]) {
                count[v] = (count[v] + count[u]) % MOD;
                min[v] = std::min(min[v], min[u] + 1);
                max[v] = std::max(max[v], max[u] + 1);
            }
        }
    }
    std::cout << cost[n] << ' ' << count[n] << ' ';
    std::cout << min[n] << ' ' << max[n] << '\n';
}
