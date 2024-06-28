/*

CSES: Graph Algorithms: Cycle Finding

You are given a directed, weighted graph with n vertices and m edges. Each edge
(u, v) has a weight w. Your task is to detect if there is a negative weight
cycle and print out a description of such a cycle. If there is no negative
weight cycle, print "NO".

Constraints:
    1 <= n <= 2500
    1 <= m <= 5000
    1 <= u, v <= n
    -1,000,000,000 <= w <= 1,000,000,000

Example Input:
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2

Example Output:
YES
1 2 4 1

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

To solve this problem we can use the Bellman-Ford algorithm. When performing
relaxation, store the "relaxant" or "parent" of each vertex. For example, if we
relax over the edge (u, v, w), store parent[v] = u. This is useful here because
relaxations will propagate outward from negative weight cycles. Perform the n-1
iterations of Bellman-Ford. Then on the n'th iteration, if a relaxation occurs
we can travel backwards along the path until we find the cycle. Also, there may
not be a path from vertex 1 to the cycle, so we need to perform relaxations
even if d[u] = "infinity".

*/

#include <iostream>
#include <vector>

const long long INF = 3e18;
typedef std::vector<std::vector<std::pair<int, int>>> Graph;
Graph g;

struct Edge {
    int u, v, w;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    g = Graph(n + 1);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
        g[edges[i].u].emplace_back(edges[i].v, edges[i].w);
    }
    int cur = -1;
    std::vector<long long> d(n + 1, INF), parent(n + 1, -1);
    d[1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (const Edge& e : edges) {
            if (d[e.u] + e.w < d[e.v]) {
                d[e.v] = d[e.u] + e.w;
                parent[e.v] = e.u;
                if (i == n) {
                    cur = e.v;
                    break;
                }
            }
        }
    }
    if (cur == -1) {
        std::cout << "NO" << '\n';
        return 0;
    }
    std::vector<bool> found(n + 1, 0);
    while (!found[cur]) {
        found[cur] = true;
        cur = parent[cur];
    }
    int start = cur;
    std::vector<int> cycle = { start };
    do {
        cur = parent[cur];
        cycle.push_back(cur);
    }
    while (cur != start);
    std::cout << "YES" << '\n';
    for (int i = (int) cycle.size() - 1; i >= 0; --i) {
        std::cout << cycle[i] << " \n"[i == 0];
    }
}
