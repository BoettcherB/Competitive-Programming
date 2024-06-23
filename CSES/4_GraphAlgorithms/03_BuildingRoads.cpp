/*

CSES: Graph Algorithms: Building Roads

You are given an undirected, unweighted graph with n vertices and m edges. Find
the number of edges that need to be added so that for every pair of vertices u
and v, there is a path from u to v. Print the number of edges needed and the
edges themselves (you can print any solution).

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    No 2 edges go between the same pair of vertices
    No edge begins and ends at the same vertex

Example Input:
4 2
1 2
3 4

Example Output:
1
2 3

The number of roads that need to be built is just the number of connected
components minus 1. The number of connected components can be found using dfs
or flood fill. Since it does not matter which roads we build, we can choose any
vertex from each component and connect the components using an edge between
these chosen vertices.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

void dfs(int v, Graph& g, std::vector<bool>& visited) {
    visited[v] = true;
    for (int adj : g[v]) {
        if (!visited[adj]) {
            dfs(adj, g, visited);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Graph g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::vector<bool> visited(n + 1);
    std::vector<int> comp;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            comp.push_back(i);
            dfs(i, g, visited);
        }
    }
    std::cout << comp.size() - 1 << '\n';
    for (int i = 1; i < (int) comp.size(); ++i) {
        std::cout << comp[i - 1] << ' ' << comp[i] << '\n';
    }
}
