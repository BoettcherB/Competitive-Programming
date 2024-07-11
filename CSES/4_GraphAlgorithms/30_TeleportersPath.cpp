/*

CSES: Graph Algorithms: Teleporters Path

You are given a directed graph with n vertices and m edges. Your task is to
travel from vertex 1 to vertex n while traversing all edges exactly once. Print
out the vertices you will visit, in order. If this is not possible, print
"IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n

Example Input:
5 6
1 2
1 3
2 4
2 5
3 1
4 2

Example Output:
1 3 1 2 4 2 5

This problem can be solved by finding an Eulerian Path that starts at vertex 1
and ends at vertex n. First of all, make sure it is possible for there to be an
Eulerian Path by making sure that all vertices except 1 and n have the same in
and out degrees. Vertex 1 must have out[1] + 1 == in[1] and vertex n must have
in[n] + 1 == out[n]. Then, run dfs starting at vertex 1 and remove edges from
the graph as they are traversed. Once a vertex has no more unexplored outgoing
paths, add it to the back of the Eulerian path. Once the dfs has finished, if
the path is not exactly length m + 1, there is no valid path.

*/

#include <iostream>
#include <vector>
#include <list>

typedef std::vector<std::vector<int>> Graph;

std::list<int> path;

void dfs(int u, Graph& g) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v, g);
    }
    path.push_front(u);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    Graph g(n + 1);
    std::vector<int> in(n + 1), out(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        ++out[u];
        ++in[v];
    }
    
    bool ok = out[1] - in[1] == 1 && in[n] - out[n] == 1;
    for (int i = 2; i < n; ++i) {
        if (in[i] != out[i])
            ok = false;
    }
    if (ok) {
        dfs(1, g);
        if ((int) path.size() == m + 1) {
            for (int u : path) {
                std::cout << u << ' ';
            }
            std::cout << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE" << '\n';
}
