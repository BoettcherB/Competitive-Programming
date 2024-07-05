/*

CSES: Graph Algorithms: Planets Cycles

You are given a directed graph with n vertices. Each vertex u has 1 outgoing
edge to a vertex v (u, v). Your task is to find, for each vertex, the number of
edges you can traverse before reaching a vertex you have already encountered.

Constraints:
    1 <= n <= 200,000
    1 <= v <= n

Example Input:
5
2 4 3 1 4

Example Output:
3 3 1 3 4

The graph in this problem is a functional graph, or a directed graph where each
vertex has 1 outgoing edge. These graphs consist of 1 or more components, each
with a directed cycle and some paths leading to the cycle.

For each vertex, we need to find which componenet it is in, as well as its
distance from its component's cycle. We can find these values using dfs. We
also need to find the number of vertices in each cycle. The answer for each
vertex is the distance from the vertex to the cycle plus the number of vertices
in the cycle.

*/

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> to, dist, component;
std::vector<bool> visited;

void dfs(int start, int& comp) {
    std::vector<int> nodes;
    int cur = start;
    while (!visited[cur]) {
        visited[cur] = true;
        nodes.push_back(cur);
        cur = to[cur];
    }
    int n = (int) nodes.size();
    int pos = n;
    if (dist[cur] == -1) {
        ++comp;
        pos = std::find(nodes.begin(), nodes.end(), cur) - nodes.begin();
        for (int i = pos; i < n; ++i) {
            dist[nodes[i]] = 0;
            component[nodes[i]] = comp;
        }
    }
    for (int i = pos - 1; i >= 0; --i) {
        dist[nodes[i]] = 1 + dist[to[nodes[i]]];
        component[nodes[i]] = component[to[nodes[i]]];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n;
    std::cin >> n;
    to = component = dist = std::vector<int>(n + 1, -1);
    visited = std::vector<bool>(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> to[i];
    }
    int comp = -1;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, comp);
        }
    }
    ++comp;
    std::vector<int> numOnCycle(comp);
    for (int i = 1; i <= n; ++i) {
        numOnCycle[component[i]] += (dist[i] == 0);
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << dist[i] + numOnCycle[component[i]] << " \n"[i == n];
    }
}
