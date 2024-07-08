/*

CSES: Graph Algorithms: Coin Collector

You are given a directed, unweighted graph with n vertices and m edges. Each
vertex has w coins. Whenever you travel to a vertex (for the first time), you
take all the coins at that vertex. Your task is to maximize the number of coins
you can collect if you can freely choose your starting and ending vertices.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= w <= 1,000,000,000
    1 <= u, v <= n

Example Input:
4 4
4 5 2 7
1 2
2 1
1 3
2 4

Example Output:
16

First of all, if we are at vertex u, we freely travel to all vertices in u's
strongly connected component. Therefore, we can simplify the problem by
reducing the graph to a graph of strongly connected components. The number of
coins in each SCC is the sum of the coins at each vertex of the component. Now,
we need to find a path through the component graph that maximizes our coins.
First, perform topological sort on the components. Then, let dp[i] be the max
number of coins we can collect if we start at component i. To find dp[i], loop
through all the children v1, v2, ..., vk  of i. dp[i] = w[i] + max(dp[v1], ...,
dp[vk]) where w[i] is the number of coins in component i. Kosaraju's algorithm
is very useful here since it processes the strongly connected components in
topological order.

*/

#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<std::vector<int>> Graph;

std::vector<int> visited, comp;
std::stack<int> s;

void dfs1(int u, const Graph& g) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v])
            dfs1(v, g);
    }
    s.push(u);
}

void dfs2(int u, const Graph& g, int c) {
    comp[u] = c;
    for (int v : g[u]) {
        if (comp[v] == 0)
            dfs2(v, g, c);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> w(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> w[i];
    }
    Graph g(n + 1), g2(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g2[v].push_back(u);
    }
    comp = visited = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfs1(i, g);
    }
    int c = 0;
    while (!s.empty()) {
        if (comp[s.top()] == 0)
            dfs2(s.top(), g2, ++c);
        s.pop();
    }
    Graph comps(c + 1);
    for (int u = 1; u <= n; ++u) {
        for (int v : g[u]) {
            if (comp[u] == comp[v]) continue;
            comps[comp[u]].push_back(comp[v]);
        }
    }
    std::vector<long long> compWeights(c + 1), dp(c + 1);
    for (int i = 1; i <= n; ++i) {
        compWeights[comp[i]] += w[i];
    }
    long long res = 0;
    for (int i = c; i > 0; --i) {
        for (int adj : comps[i]) {
            dp[i] = std::max(dp[i], dp[adj]);
        }
        dp[i] += compWeights[i];
        res = std::max(res, dp[i]);
    }
    std::cout << res << '\n';
}
