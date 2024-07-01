/*

CSES: Graph Algorithms: Course Schedule

You are given a directed, unweighted graph with n vertices and m edges. Each
vertex represents a course and each edge (u, v) means that course u must be
completed before course v. Find an order in which you can complete all courses.
If there is no solution, print "IMPOSSIBLE".

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n

Example Input:
5 3
1 2
3 1
4 5

Example Output:
3 4 1 5 2

To solve this problem, we need to determine if the graph is a DAG, and if so,
print out a topological ordering of the vertices. We can use Kahn's algorithm
to find a topological ordering: repeatedly find vertices with an in-degree 0,
"remove" them from the graph, and then update the in-degree of all adjacent
vertices.

*/

#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> in(n + 1), order;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        ++in[v];
    }
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0)
            q.push(i);
    }
    int count = (int) q.size();
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (--in[v] == 0) {
                q.push(v);
                ++count;
            }
        }
    }
    if (count < n) {
        std::cout << "IMPOSSIBLE" << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << order[i] << " \n"[i == n - 1];
    }
}
