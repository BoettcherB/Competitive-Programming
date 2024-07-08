/*

Problem Statement: https://atcoder.jp/contests/abc361/tasks/abc361_e

The first thing to notice here is that it is always beneficial to start and end
the path at a leaf node. This way, we only have to travel across the edge
connecting the leaf to the rest of the tree once. Let's say we select a random
leaf u as the start of the path and a leaf v as the end of the path. If we
trace a path from u to v that visits all nodes at least once, we can see that
we traverse all edges twice, except for the edges on the direct path from u to
v which are only traversed once. This means that the best solution is the one
where the cost of the path from u to v is maximized (because we only traverse
the edges of that path once).

In other words, we have reduced the problem to finding the longest path in a
tree, which can be solved using 2 passes of dfs. First, select a random start
vertex A and find the longest path from A to any other vertex. Then, start the
second dfs at the vertex B that was furthest from A. The path from B to C (the
farthest vertex from B) is the longest path in the tree. The final answer is
the (sum of all edge weights) * 2 - (the length of the path from B to C).

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::pair<int, int>>> Graph;
Graph g;

std::pair<long long, int> dfs(int u, int p, long long cost) {
    std::pair<long long, int> res = { cost, u };
    for (auto adj : g[u]) {
        int v = adj.first, w = adj.second;
        if (v == p) continue;
        res = std::max(res, dfs(v, u, cost + w));
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    g = Graph(n + 1);
    long long sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        sum += w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    long long maxPath = dfs(dfs(1, -1, 0).second, -1, 0).first;
    std::cout << sum * 2 - maxPath << '\n';
}
