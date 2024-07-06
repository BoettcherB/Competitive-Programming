/*

CSES: Graph Algorithms: Flight Routes Check

You are given a directed, unweighted graph with n vertices and m edges. Your
task is to determine if it is possible to travel from any vertex to any other
vertex. If so, print "YES". If not, print "NO" and a pair of vertices (u, v)
where it is not possible to travel from u to v.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n

Example Input:
4 5
1 2
2 3
3 1
1 4
3 4

Example Output:
NO
4 2

For this problem, we need to determine if the graph is strongly connected. One
important thing to realize about strongly connected graphs is that if it is
possible to travel from vertex 1 to every other vertex and to vertex 1 from
every other vertex, then it is possible to travel from any vertex to any other
vertex.

One (pretty complicated) way to solve this problem is with dfs. We can run an
initial check to make sure that no vertices have an in-degree or an out-degree
of 0. We can also run dfs from vertex 1 to make sure we can reach all vertices
from vertex 1. We will call a vertex u good if there is a path from 1 to u and
from u to 1. Initially mark 1 as good. Then run dfs starting at vertex 1. If we
are at vertex u and we encounter an unvisited vertex v, mark v as visited and
store u as a 'parent' of v (since this is a graph, not a tree, a vertex can
have multiple 'parents'). If we are at u and encounter a 'good' vertex v, then
that means there is a cycle from a good vertex to another good vertex. Run a
backtrack dfs through the parents of v, marking each vertex as good. Run dfs
from every good vertex encountered (we can add vertices to a queue when they
are marked good). If, at the end, a vertex v is not marked good, it is not
possible to reach vertex 1 from vertex v.

A much simpler method to solve this problem is to use a reverse graph. We can
check if it is possible to reach all vertices from vertex 1 using dfs. Then, we
can flip all the edges and run dfs from vertex 1 again. If we are not able to
reach a vertex in the reverse graph, then it is not possible to reach vertex 1
from that vertex in the actual graph.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

void dfs(int u, const Graph& g, std::vector<bool>& visited) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v])
            dfs(v, g, visited);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Graph g(n + 1), g2(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g2[v].push_back(u);
    }
    std::vector<bool> v1(n + 1), v2(n + 1);
    dfs(1, g, v1);
    dfs(1, g2, v2);
    for (int i = 1; i <= n; ++i) {
        if (!v1[i]) {
            std::cout << "NO\n" << 1 << ' ' << i << '\n';
            return 0;
        }
        if (!v2[i]) {
            std::cout << "NO\n" << i << ' ' << 1 << '\n';
            return 0;
        }
    }
    std::cout << "YES" << '\n';
}
