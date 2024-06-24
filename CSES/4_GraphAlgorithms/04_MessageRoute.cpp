/*

CSES: Graph Algorithms: Message Route

You are given an undirected, unweighted graph with n vertices and m edges. Your
task is to determine the shortest path from vertex 1 to vertex n, and print out
the vertices along the path. If there is no path, print "IMPOSSIBLE".

Constraints:
    2 <= n <= 100,000
    1 <= m <= 200,000
    1 <= a, b <= n
    Every edge is between 2 different vertices
    No 2 edges connect the same pair of vertices

Example Input:
5 5
1 2
1 3
1 4
2 3
5 4

Example Output:
3
1 4 5

This is a standard shortest path problem that can be solved with bfs. Keep a
queue of vertices found so far. When a vertex is dequeued, check its neighbors.
If a neighbor has not been visited, mark it as visited and add it to the queue.
For this problem, we should also store, for each vertex v, the previous vertex
that led to v. This can be updated as v is added to the queue. Once n is found,
backtrack along the path until vertex 1 is found to recreate the path.

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
    std::vector<int> from(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::queue<int> q;
    q.emplace(1);
    while (!q.empty()) {
        int cur = q.front();
        if (cur == n)
            break;
        q.pop();
        for (int adj : g[cur]) {
            if (from[adj] == 0) {
                from[adj] = cur;
                q.emplace(adj);
            }
        }
    }
    if (from[n] == 0) {
        std::cout << "IMPOSSIBLE" << '\n';
        return 0;
    }
    int cur = n;
    std::vector<int> path = { n };
    while (cur != 1) {
        cur = from[cur];
        path.push_back(cur);
    }
    std::cout << path.size() << '\n';
    for (int i = (int) path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " \n"[i == 0];
    }
}
