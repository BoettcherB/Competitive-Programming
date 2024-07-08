/*

CSES: Graph Algorithms: Giant Pizza

There are n family members who come together to order a pizza with m toppings.
Each family member has 2 preferences about the toppings: "I like/dislike
topping x". Find a way to add toppings to the pizza such that every family
member has at least one of their preferences satisfied (a topping they like is
included or a topping they dislike is not included). If there is no way to do
this, print "IMPOSSIBLE".

Constraints:
    1 <= n, m <= 100,000
    1 <= x <= m

Example Input:
3 5
+ 1 + 2
- 1 + 3
+ 4 - 2

Example Output:
- + + + -

This is the 2-SAT problem, which involves assigning bool values to m variables
to solve a boolean formula in CNF (conjunctive normal form). Each clause will
have exactly 2 variables. A clause in this problem is a single family member's
preferences. The 2-SAT problem can be solved using directed graphs. For each
clause, if the first term is false, then the second term must be true, and if
the second term is false, then the first term must be true. We can create
directed edges between variables showing these requirements. For example, if we
have the clause (A || !B), there will be an edge (!A, !B) and an edge (B, A).
If A is false, B must be false, and if B is true, then A must be true. (If we
have m variables there will be 2m vertices in the graph). Once we have our
graph, we need to find all the strongly connected components of the graph and
process them in topological order. For each variable x, if both x and !x are in
the same SCC, there is no solution. Otherwise, we assign a variable x the value
true if the scc of !x is before the scc of x in the topological ordering of
scc's, and false if the scc of x is before the scc of !x. Kosaraju's algorithm
works well for this problem because on the second pass of dfs, the scc's are
processed in topological order.

*/

#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<std::vector<int>> Graph;

std::stack<int> s;
std::vector<int> visited, comp;

void add_clause(int a, bool va, int b, bool vb, Graph& g1, Graph& g2) {
    a = 2 * a ^ (!va);
    b = 2 * b ^ (!vb);
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

    int clauses, vars;
    std::cin >> clauses >> vars;
    int n = 2 * vars;
    Graph g(n), g2(n);
    for (int i = 0; i < clauses; ++i) {
        char c1, c2;
        int v1, v2;
        std::cin >> c1 >> v1 >> c2 >> v2;
        --v1; --v2;
        add_clause(v1, c1 == '+', v2, c2 == '+', g, g2);
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
    std::vector<char> assignment(vars);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1]) {
            std::cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
        assignment[i / 2] = comp[i] > comp[i + 1] ? '+' : '-';
    }
    for (int i = 0; i < vars; ++i) {
        std::cout << assignment[i] << " \n"[i == vars];
    }
}
