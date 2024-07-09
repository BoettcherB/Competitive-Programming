/*

CSES: Graph Algorithms: Mail Delivery

You are given an undirected graph with n vertices and m edges. Your task is to
start at vertex 1, traverse all edges exactly once, and end up back at vertex
1. Print out the vertices that you will visit in order. If such a path is not
possible, print "IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    There are no self loops
    No 2 edges go between the same pair of vertices

Example Input:
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5

Example Output:
1 2 6 3 2 4 5 3 1

For this problem, we want to find if the graph has an Eulerian Circuit. First
of all, each vertex in the graph must have an even degree. If any vertex has an
odd degree we can immediately print IMPOSSIBLE. Then, we can run dfs from the
start vertex and remove edges as we go. (This is important since it is possible
that all edges are connected to one vertex. We will visit that vertex m/2 times
and each time we would have to loop through each edge to see if they are used,
which would be O(m^2)). Since each vertex has even degree, it's not possible to
get stuck anywhere except at the end of the cirucit. Therefore, if we reach a
dead end in the graph, we can add that vertex to the end of the circuit. If we
finish the dfs and the size of our circuit is not exactly m + 1, then there are
multiple components in the graph and a Eulerian Circuit is not possible.

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

typedef std::vector<std::vector<int>> Graph;

struct Edge {
    int u, v;
    bool used = false;
};

std::list<int> circuit;
std::vector<Edge> edges;

void dfs(int u, Graph& g) {
    while (!g[u].empty()) {
        int i = g[u].back();
        g[u].pop_back();
        if (!edges[i].used) {
            edges[i].used = true;
            dfs(edges[i].u == u ? edges[i].v : edges[i].u, g);
        }
    }
    circuit.push_front(u);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    Graph g(n + 1);
    edges = std::vector<Edge>(m);
    std::vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v;
        g[edges[i].u].push_back(i);
        g[edges[i].v].push_back(i);
        ++deg[edges[i].u];
        ++deg[edges[i].v];
    }
    if (std::any_of(deg.begin(), deg.end(), [](int d){return d % 2 == 1;})) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    dfs(1, g);
    if ((int) circuit.size() != m + 1)
        std::cout << "IMPOSSIBLE" << '\n';
    else {
        for (int u : circuit) {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }
}
