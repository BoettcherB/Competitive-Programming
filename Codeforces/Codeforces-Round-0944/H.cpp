/*

Problem Statement: https://codeforces.com/contest/1971/problem/H

This is a variation of the 2-SAT problem. Here, each clause has 3 terms but 2
of them must be true. We can convert this into 2-SAT by realizing that, for
every pair of terms in a clause, they cannot both be false. We can split each
3-term clause into 3 2-term clauses: (A || !B || C) ==> (A || !B) && (A || C)
&& (!B || C). This new problem can be solved using the 2-SAT method: Kosaraju's
algorithm to find SCC's and processing the SCC's in topological order.

*/

#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<std::vector<int>> Graph;

std::stack<int> s;
std::vector<int> visited, comp;

void add_clause(int a, bool va, int b, bool vb, Graph& g1, Graph& g2) {
    a = (std::abs(a) - 1) * 2 ^ (!va);
    b = (std::abs(b) - 1) * 2 ^ (!vb);
    int neg_a = a ^ 1, neg_b = b ^ 1;
    g1[neg_a].push_back(b);
    g1[neg_b].push_back(a);
    g2[b].push_back(neg_a);
    g2[a].push_back(neg_b);
}

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

    int tc;
    std::cin >> tc;
    while (tc--) {
        int clauses;
        std::cin >> clauses;
        std::vector<std::vector<int>> m(3, std::vector<int>(clauses));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < clauses; ++j) {
                std::cin >> m[i][j];
            }
        }
        int n = 2 * clauses;
        Graph g(n), g2(n);
        for (int i = 0; i < clauses; ++i) {
            add_clause(m[0][i], m[0][i] > 0, m[1][i], m[1][i] > 0, g, g2);
            add_clause(m[0][i], m[0][i] > 0, m[2][i], m[2][i] > 0, g, g2);
            add_clause(m[1][i], m[1][i] > 0, m[2][i], m[2][i] > 0, g, g2);
        }
        visited = comp = std::vector<int>(n);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs1(i, g);
        }
        int c = 0;
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            if (comp[u] == 0)
                dfs2(u, g2, ++c);
        }
        bool ok = true;
        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i + 1]) {
                ok = false;
                break;
            }
        }
        std::cout << (ok ? "YES" : "NO") << '\n';
    }
}
