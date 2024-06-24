/*

CSES: Graph Algorithms: Building Teams

You are given an undirected, unweighted graph with n vertices and m edges. Your
task is to split up the vertices into 2 teams such that there are no edges
between vertices in the same team. If there is no solution, print "IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= a, b <= n
    Every edge is between 2 different vertices
    No 2 edges connect the same pair of vertices

Example Input:
5 3
1 2
1 3
4 5

Example Output:
1 2 2 1 2

For there to be a solution, the graph needs to be bipartite and have no odd
length cycles. To find a solution, we can use dfs and greedily assign each
vertex a team based on the assignments of its neighbors. If a neighbor was
already assigned to team 1, then the current vertex must be in team 2. If one
neighbor was assigned to team 1 and a second neighbor was assigned to team 2,
then there is no solution.

Note: below I use t ^ 3 to find the 'other' team. This is because 1 ^ 3 == 2
and 2 ^ 3 == 1.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;
Graph g;
std::vector<int> team;

void dfs(int v, int t) {
    team[v] = t;
    for (int adj : g[v]) {
        if (team[adj] == t) {
            std::cout << "IMPOSSIBLE" << '\n';
            std::exit(0);
        }
        if (team[adj] == 0) {
            dfs(adj, t ^ 3);
        }
    }
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
        g[v].push_back(u);
    }
    team = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (team[i] == 0) {
            dfs(i, 1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << team[i] << " \n"[i == n];
    }
}
