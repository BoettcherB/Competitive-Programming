/*

CSES: Graph Algorithms: Download Speed

You are given a directed, weighted graph with n vertices and m edges. Each edge
(u, v) has a capacity c, which represents the transfer rate of data between two
computers u and v. Using the connections in the graph, what is the maximum
transfer rate from vertex 1 to vertex n?

Constraints:
    1 <= n <= 500
    1 <= m <= 1000
    1 <= u, v <= n
    1 <= c <= 1,000,000,000

Example Input:
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3

Example Output:
6

This is a max flow problem which can be solved with the Ford-Fulkerson method.
This method involves finding paths from the source node (1) to the sink node
(n) and updating the flow across each edge of the path by the bottleneck (or
min capacity edge), while also increasing flow along residual edges by the
same amount. The method used for finding paths through the network is Dinic's
algorithm, which uses bfs to fill a level[] array (which holds the distance
of each vertex from the source) and then uses dfs to find paths that only
increase the level at each vertex.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class MaxFlow {
    struct Edge {
        int u, v, residualIndex;
        long long capacity, flow;

        Edge(int u, int v, long long c) : u{ u }, v{ v }, capacity{ c } {
            flow = 0;
            residualIndex = -1;
        }

        long long cap() const {
            return capacity - flow;
        }
    };

    int n, source, sink, tok = 1;
    std::vector<std::vector<int>> graph;
    std::vector<Edge> edges;
    std::vector<int> level, visited, next;

public:
    MaxFlow(int n, int S, int T) : n{ n }, source{ S }, sink{ T } {
        graph = std::vector<std::vector<int>>(n);
        level = visited = next = std::vector<int>(n);
    }

    void addEdge(int u, int v, long long capacity) {
        edges.emplace_back(u, v, capacity);
        edges.emplace_back(v, u, 0);
        int e = (int) edges.size() - 2;
        int r = (int) edges.size() - 1;
        edges[e].residualIndex = r;
        edges[r].residualIndex = e;
        graph[u].push_back(e);
        graph[v].push_back(r);
    }

    long long maxFlow() {
        long long totalFlow = 0;
        while (bfs()) {
            ++tok;
            while (true) {
                std::fill(next.begin(), next.end(), 0);
                long long pushed = dfs(source, 3e18);
                totalFlow += pushed;
                if (pushed == 0)
                    break;
            }
        }
        return totalFlow;
    }

private:
    bool bfs() {
        std::fill(level.begin(), level.end(), -1);
        std::queue<std::pair<int, int>> q;
        q.emplace(source, 1);
        visited[source] = ++tok;
        while (!q.empty()) {
            int node = q.front().first, L = q.front().second;
            q.pop();
            level[node] = L;
            if (node == sink)
                break;
            for (int ei : graph[node]) {
                Edge& e = edges[ei];
                if (visited[e.v] != tok && e.cap() > 0) {
                    q.emplace(e.v, L + 1);
                    visited[e.v] = tok;
                }
            }
        }
        return level[sink] != -1;
    }

    long long dfs(int u, long long bottleneck) {
        visited[u] = tok;
        if (u == sink)
            return bottleneck;
        int numOutgoing = (int) graph[u].size();
        while (next[u] < numOutgoing) {
            Edge& e = edges[graph[u][next[u]++]];
            if (visited[e.v] != tok && e.cap() && level[e.v] > level[u]) {
                long long flow = dfs(e.v, std::min(bottleneck, e.cap()));
                if (flow > 0) {
                    e.flow += flow;
                    edges[e.residualIndex].flow -= flow;
                    return flow;
                }
            }
        }
        return 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    MaxFlow flow(n + 1, 1, n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        flow.addEdge(u, v, c);
    }
    std::cout << flow.maxFlow() << '\n';
}
