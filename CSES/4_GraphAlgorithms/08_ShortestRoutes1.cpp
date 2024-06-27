/*

CSES: Graph Algorithms: Shortest Routes 1

You are given a weighted, directed graph with n vertices and m edges. Each edge
(u, v) is a one-way route and has a cost c. Find the length of the shortest
path from vertex 1 to all other vertices.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    1 <= c <= 1,000,000,000
    There is a path from vertex 1 to all other vertices

Example Input:
3 4
1 2 6
1 3 2
3 2 3
1 3 4

Example Output:
0 5 2

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

This problem can be solved using Dijkstra's algorithm. It is similar to bfs
except instead of a queue we use a min priority queue where the priorities are
the lengths of the paths to each vertex.

Below, I use a max priority queue but I flip the sign of the path length so it
still considers shorter paths first.

*/

#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        g[u].emplace_back(v, c);
    }
    std::vector<long long> dist(n + 1, -1);
    std::priority_queue<std::pair<long long, int>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        long long d = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if (dist[v] != -1) continue;
        dist[v] = -d;
        for (auto& adj : g[v]) {
            int u = adj.first, c = adj.second;
            if (dist[u] == -1) {
                pq.emplace(d - c, u);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << dist[i] << " \n"[i == n];
    }
}
