/*

You are given a directed, unweighted graph with n vertices and m edges. Two
vertices u and v belong to the same 'kingdom' if it is possible to travel from
u to v and from v to u. For each vertex, determine its kingdom (an integer from
1 to k where k is the number of kingdoms in the graph).

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n

Example Input:
5 6
1 2
2 3
3 1
3 4
4 5
5 4

Example Output:
2
1 1 1 2 2

This problem requires us to find all the strongly connected components in the
graph. We can do this using Tarjan's algorithm, which assigns the same low-link
value to all vertices in the same strongly connected component. Afterwards, we
can compress the low-link values to the range [1, k] using a map.

*/

#include <iostream>
#include <vector>
#include <stack>
#include <map>

typedef std::vector<std::vector<int>> Graph;

int id = 0;
Graph g;
std::vector<int> onStack, ids, low;
std::stack<int> s;

void dfs(int u) {
    ids[u] = low[u] = ++id;
    s.push(u);
    onStack[u] = true;
    for (int v : g[u]) {
        if (ids[v] == 0) dfs(v);
        if (onStack[v]) low[u] = std::min(low[u], low[v]);
    }
    if (low[u] == ids[u]) {
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            onStack[v] = false;
            low[v] = low[u];
            if (v == u) break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    onStack = ids = low = std::vector<int>(n + 1);
    g = Graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) {
        if (ids[i] == 0) {
            dfs(i);
        }
    }
    std::map<int, int> ind;
    id = 0;
    for (int i = 1; i <= n; ++i) {
        if (ind.find(low[i]) == ind.end())
            ind[low[i]] = ++id;
        ids[i] = ind[low[i]];
    }
    std::cout << ind.size() << '\n';
    for (int i = 1; i <= n; ++i) {
        std::cout << ids[i] << " \n"[i == n];
    }
}
