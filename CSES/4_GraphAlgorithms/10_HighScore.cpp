/*

You are given a directed, weighted graph with n vertices and m edges. Each edge
(u, v) has a weight w. You start at vertex 1 and end at vertex n. Whenever you
cross an edge, that edge's weight is added to your score. Print the maximum
score you can achieve. If you can achieve an arbitrarily large score, print -1.

Constraints:
    1 <= n <= 2500
    1 <= m <= 5000
    1 <= u, v <= n
    -1,000,000,000 <= w <= 1,000,000,000

Example Input:
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4

Example Output:
5

Note that it is possible for there to be self-loops and multiple edges between
a single pair of vertices.

To solve this problem we can use the Bellman-Ford algorithm. This algorithm
allows us to find the shortest path from a vertex to all other vertices even if
there are negative edge weights. It is also useful here because it allows us
to detect negative weight cycles. For this problem, we are looking for positive
cycles, not negative cycles, though the logic is exactly the same. We just need
to initialize all distances to -infinity instead of infinity and relaxation on
an edge (u, v, w) occurs when d[u] + w > d[v] (instead of less than).

For this problem, just detecting a positive cycle is not enough. There must be
a path from vertex 1 to the positive cycle, as well as a path from the positive
cycle to vertex n. To handle these, we should only apply relaxation over an
edge (u, v, w) if d[u] != -infinity, and we should apply relazation over 2*n
steps. Also, we need to watch out for cases where u is on a positive weight
cycle and d[v] is very large. In this case, relaxation over the edge (u, v, w)
might not occur this round (or in any of the 2*n rounds) but it will occur
eventually.

*/

#include <iostream>
#include <vector>

const long long INF = 3e18;

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
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    std::vector<long long> dist(n + 1, -INF);
    std::vector<bool> updating(n + 1);
    dist[1] = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        for (const Edge& e : edges) {
            if (dist[e.u] == -INF)
                continue;
            if (dist[e.u] + e.w > dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updating[e.v] = i >= n;
            }
            if (updating[e.u]) {
                updating[e.v] = true;
            }
        }
    }
    std::cout << (updating[n] ? -1 : dist[n]) << '\n';
}
