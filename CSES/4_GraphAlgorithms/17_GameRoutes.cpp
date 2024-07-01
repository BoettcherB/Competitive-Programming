/*

You are given an unweighted DAG with n vertices and m edges. Your task is to
find the number of paths from vertex 1 to vertex n.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    The graph has no directed cycles

Example Input:
4 5
1 2
2 4
1 3
3 4
1 4

Example Output:
3

This problem can be solved using topological sort and dp. Find a topological
ordering of the vertices. Initially, paths[1] = 1. Then, for all edges (u, v)
going into vertex v, paths[v] += paths[u]. The answer is paths[n].

*/

#include <iostream>
#include <vector>
#include <queue>

const int MOD = 1e9 + 7;
const long long INF = 3e18;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> in(n + 1), order;
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
    std::vector<long long> paths(n + 1, INF);
    paths[1] = 1;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (paths[u] == INF) continue;
        for (int v : g[u]) {
            if (paths[v] == INF)
                paths[v] = 0;
            paths[v] = (paths[v] + paths[u]) % MOD;
        }
    }
    std::cout << (paths[n] == INF ? 0 : paths[n]) << '\n';
}
