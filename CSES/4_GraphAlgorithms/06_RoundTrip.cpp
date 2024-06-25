/*

CSES: Graph Algorithms: Round Trip

You are given an undirected, unweighted graph with n vertices and m edges. Your
task is to print out any cycle in the graph. If the graph does not contain a
cycle, print "IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= a, b <= n
    Every edge is between 2 different vertices
    No 2 edges connect the same pair of vertices

Example Input:
5 6
1 3
1 2
5 3
1 5
2 4
4 5

Example Output:
4
3 5 1 3

We can use dfs to detect cycles in a graph. Run dfs while storing the parent of
each vertex. If we find a node that we have already visited, backtrack along
the path until we reach that node again while adding each node along the way to
the path.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;
Graph g;
std::vector<int> prev;

void printPath(int cur, int v) {
    std::vector<int> path = { v, cur };
    while (cur != v) {
        cur = prev[cur];
        path.push_back(cur);
    }
    int n = (int) path.size();
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << path[i] << " \n"[i == n - 1];
    }
    std::exit(0);
}

void dfs(int v, int p) {
    prev[v] = p;
    for (int adj : g[v]) {
        if (adj == p) continue;
        if (prev[adj] != 0)
            printPath(v, adj);
        dfs(adj, v);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    g = Graph(n + 1);
    prev = std::vector<int>(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        if (prev[i] == 0) {
            dfs(i, -1);
        }
    }
    std::cout << "IMPOSSIBLE" << '\n';
}
