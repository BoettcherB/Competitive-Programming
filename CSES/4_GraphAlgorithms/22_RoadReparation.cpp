/*

CSES: Graph Algorithms: Road Reparation

You are given an undirected, weighted graph with n vertices and m edges. Each
edge (u, v) has a weight w. Your task is to find a subset of edges with minimum
weight such that it is possible to travel between any pair of vertices.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    1 <= c \le 10^9
    There are no self-loops
    There cannot be 2 edges between the same pair of vertices

Example Input:
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

Example Output:
14

We need to find a minimum spanning tree of the graph. This can be done with
Krsukal's algorithm. Sort the edges by weight. Then, try adding each edge (u,v)
to the graph. If u and v are already in the same component, skip the edge. We
can quickly determine if u and v are in the same component using a DSU data
structure. If we are not able to add n - 1 edges to the graph, then it is not
possible to create a minimum spanning tree (the graph is not connected).

*/

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> parent, size;

int find(int v) {
    return v == parent[v] ? v : parent[v] = find(parent[v]);
}

bool merge(int a, int b) {
    if ((a = find(a)) != (b = find(b))) {
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
    return false;
}

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const {
        return w < o.w;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    parent = size = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        size[i] = 1;
    }
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    std::sort(edges.begin(), edges.end());
    long long res = 0, count = 0;
    for (const Edge& edge : edges) {
        if (merge(edge.u, edge.v)) {
            res += edge.w;
            ++count;
        }
    }
    if (count == n - 1)
        std::cout << res << '\n';
    else
        std::cout << "IMPOSSIBLE" << '\n';
}
