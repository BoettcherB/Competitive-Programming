/*

CSES: Graph Algorithms: Planets Queries 2

You are given a directed graph with n vertices. Each vertex u has 1 outgoing
edge to a vertex v (u, v). You are also given q queries, each containing 2
integers u and v. For each query, determine the number of edges you need to
traverse to go from u to v. If it is not possible, print -1.

Constraints:
    1 <= n, q <= 200,000
    1 <= u, v <= n

Example Input:
5 3
2 3 2 3 2
1 2
1 3
1 4

Example Output:
1
2
-1

The graph in this problem is a functional graph, or a directed graph where each
vertex has 1 outgoing edge. These graphs consist of 1 or more components, each
with a directed cycle and some paths leading to the cycle.

For each vertex v, we need to determine which component it is in, the distance
of v to its component's cycle, and (if it is on the cycle) its index on the
cycle (compared to a randomly chosen vertex on the cycle). We can find v's
component and distance from the cycle using dfs. Then, using these values,
we can find each vertex's index along the cycle and the number of vertices
in each cycle.

To be able to travel from u to v, u and v must both be in same component and
the distance of u to the cycle (dist[u]) must be >= dist[v]. We then need to
travel along dist[u]-dist[v] edges. If we are not at v and v is not on the
cycle, then it is impossible to reach v. If v is on the cycle, we need to
travel along the cycle until we reach v (which can be done in O(1) time using
u and v's index along the cycle (which we computed earlier).

We can use a technique called binary lifting to pre-compute the vertex we will
end up on if we travel across 1 edge, 2 edges, 4 edges, etc. (all powers of 2).
To find the result vertex if we want to travel across k edges, we can find the
msb (most significant bit) of k and travel across 1 << msb edges in O(1) time.
Then, remove the msb from k. Keep doing this until k is 0.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int P = 20;
std::vector<int> to, dist, component;
std::vector<bool> visited;
std::vector<std::vector<int>> successor;

int succ(int x, int k = 1) {
    int val = k;
    while (val) {
        int bit = (int) std::log2(val);
        x = successor[x][bit];
        val -= 1 << bit;
    }
    return x;
}

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

    int n, q;
    std::cin >> n >> q;
    to = component = dist = std::vector<int>(n + 1, -1);
    visited = std::vector<bool>(n + 1);
    successor = std::vector<std::vector<int>>(n + 1, std::vector<int>(P));
    for (int i = 1; i <= n; ++i) {
        std::cin >> to[i];
        successor[i][0] = to[i];
    }
    for (int pow2 = 1; pow2 < P; ++pow2) {
        for (int i = 1; i <= n; ++i) {
            successor[i][pow2] = successor[successor[i][pow2 - 1]][pow2 - 1];
        }
    }
    int comp = -1;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, comp);
        }
    }
    ++comp;
    std::vector<int> cycleStart(comp), numOnCycle(comp), indexOnCycle(n + 1);
    for (int i = 1; i <= n; ++i) {
        numOnCycle[component[i]] += dist[i] == 0;
        if (dist[i] == 0 && cycleStart[component[i]] == 0) {
            cycleStart[component[i]] = i;
            int cur = i, index = 0;
            do {
                indexOnCycle[cur] = index++;
                cur = to[cur];
            } while (cur != i);
        }
    }
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        int res = -1, diff = dist[u] - dist[v];
        if (component[u] == component[v] && diff >= 0) {
            u = succ(u, diff);
            if (u == v)
                res = diff;
            else if (dist[v] == 0) {
                int d = indexOnCycle[v] - indexOnCycle[u];
                if (d < 0)
                    d += numOnCycle[component[u]];
                res = diff + d;
            }
        }
        std::cout << res << '\n';
    }
}
