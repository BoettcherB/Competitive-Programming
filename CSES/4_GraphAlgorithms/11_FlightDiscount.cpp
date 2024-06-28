/*

CSES: Graph Algorithms: Flight Discount

You are given a weighted, directed graph with n vertices and m edges. Each edge
(u, v) has a weight w. Your task is to find the minimum cost path from vertex 1
to vertex n. However, you have a coupon which allows you to cut the price of a
single edge in half. Find the cost of the minimum cost path while applying the
coupon to one edge.

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    1 <= w <= 1,000,000,000
    There is a path from vertex 1 to vertex n

Example Input:
3 4
1 2 3
2 3 1
1 3 7
2 1 5

Example Output:
2

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

One way to solve this problem is to find the distances from vertex 1 to all
other vertices (d1[n]), and the distances from vertex n to all other vertices
(dN[n]). Then, loop through each edge (u, v, w) and try cutting it in half. The
answer will be the minimum of (d1[u] + w/2 + dN[v]) for all edges. We can find
the distances from vertex n to all other vertices by setting up a second graph
where all the edges have reversed directions.

Another method to solve this problem is to first run dijkstra's to find the
distances from vertex 1 to all other vertices (d1[n]) without applying the
coupon. Then we run dijkstra's again but this time we find the distances from
1 to all other vertices while applying the coupon (d2[n]). When considering an
edge E = (u, v, w), d2[v] = min(d1[u] + w/2, d2[u] + w). ie. we can either
travel to u and then use the coupon on E, or we can use the coupon on the way
to u and then take E without the coupon.

*/

#include <iostream>
#include <vector>
#include <queue>

const long long INF = 3e18;
typedef std::vector<std::vector<std::pair<long long, long long>>> Graph;

void dijkstra(Graph& g, int start, std::vector<long long>& dists) {
    std::priority_queue<std::pair<long long, int>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        long long weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (dists[u] != INF) continue;
        dists[u] = -weight;
        for (const auto& adj : g[u]) {
            int v = adj.first, w = adj.second;
            if (dists[v] != INF) continue;
            pq.emplace(weight - w, v);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Graph g(n + 1), g_rev(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g_rev[v].emplace_back(u, w);
    }
    std::vector<long long> dist1(n + 1, INF), distN(n + 1, INF);
    dijkstra(g, 1, dist1);
    dijkstra(g_rev, n, distN);
    long long res = INF;
    for (int u = 1; u <= n; ++u) {
        for (const auto& edge : g[u]) {
            int v = edge.first, w = edge.second;
            res = std::min(res, dist1[u] + w / 2 + distN[v]);
        }
    }
    std::cout << res << '\n';
}
