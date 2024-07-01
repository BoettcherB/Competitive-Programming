/*

CSES: Graph Algorithms: Longest Flight Route

You are given an uweighted DAG with n vertices and m edges. Your goal is to
find the longest path from vertex 1 to vertex n and print out a description of
the path. If there is no such path, print "IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    The graph has no directed cycles

Example Input:
5 5
1 2
2 5
1 3
3 4
4 5

Example Output:
4
1 3 4 5

This problem can be solved by finding a topological ordering of the vertices.
Then, for each vertex u in the ordering, take each edge (u, v) and mark dist[v]
= max(dist[v], dist[u] + 1). Also keep track of the 'parent' of each vertex so
that the longest path can be reconstructed.

*/

#include <iostream>
#include <vector>
#include <queue>

const int INF = 2e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> in(n + 1), order, dist(n + 1, -INF), parent(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        ++in[v];
    }
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0)
            q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (--in[v] == 0)
                q.push(v);
        }
    }
    dist[1] = 0;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (dist[u] == -INF) continue;
        for (int v : g[u]) {
            if (dist[u] + 1 > dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + 1;
            }
        }
    }
    if (dist[n] == -INF) {
        std::cout << "IMPOSSIBLE" << '\n';
        return 0;
    }
    std::vector<int> path = { n };
    int cur = n;
    while (cur != 1) {
        cur = parent[cur];
        path.push_back(cur);
    }
    std::cout << path.size() << '\n';
    for (int i = (int) path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " \n"[i == 0];
    }
}
