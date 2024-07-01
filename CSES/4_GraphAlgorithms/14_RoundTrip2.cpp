/*

CSES: Graph Algorithms: Round Trip 2

You are given a directed, unweighted graph with n vertices and m edges. Your
task if to find a cycle in the graph and print a description of it. If there is
no cycle in the graph, print "IMPOSSIBLE".

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    There are no self-loops

Example Input:
4 5
1 3
2 1
2 4
3 2
3 4

Example Output:
4
2 1 3 2

This problem can be solved using dfs. However, unlike the previous problem
(Round Trip 1) which uses an undirected graph, we cannot immediately report a
cycle once we encounter a previously visited vertex. We can only report a cycle
if we encounter a vertex that is on the direct path from the 'start' vertex
(wherever we started the dfs) to the current vertx. We can keep 2 array: onPath
and seen. If we visit a vertex v for the first time, we mark seen[v] = true. If
we a vertex v we mark onPath[v] = true, and if we backtrack from v we mark
onPath[v] = false. We know we have found a cycle if we encounter a vertex u
where onPath[u] = true.

A common technique to solve this type of problem is to assign each vertex a
color. WHITE = unvisited. GRAY = visited but not all children fully explored
(same as onPath). BLACK = fully visited. If we encounter a GRAY vertex, then
we have found a cycle.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;
Graph g;
std::vector<int> parent, onPath, seen;

void print_cycle(int start) {
    int u = start;
    std::vector<int> cycle = { u };
    do {
        u = parent[u];
        cycle.push_back(u);
    } while (u != start);
    std::cout << cycle.size() << '\n';
    for (int i = (int) cycle.size() - 1; i >= 0; --i) {
        std::cout << cycle[i] << " \n"[i == 0];
    }
}

void dfs(int u) {
    onPath[u] = seen[u] = true;
    for (int v : g[u]) {
        if (onPath[v]) {
            parent[v] = u;
            print_cycle(v);
            std::exit(0);
        }
        if (seen[v]) continue;
        parent[v] = u;
        dfs(v);
    }
    onPath[u] = false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    g = Graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
    }
    parent = onPath = seen = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (!seen[i])
            dfs(i);
    }
    std::cout << "IMPOSSIBLE" << '\n';
}
