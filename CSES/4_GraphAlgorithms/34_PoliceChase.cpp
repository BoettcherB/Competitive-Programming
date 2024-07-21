/*

CSES: Graph Algorithms: Police Chase

You are given an unweighted, undirected graph with n vertices and m edges. Your
task is to find a set of edges S of minimum size such that if you remove all
the edges in S from the graph, there is no path from vertex 1 to vertex n.
Print the size of S and then |S| edges.

Constraints:
    2 <= n <= 500
    1 <= m <= 1000
    1 <= u, v <= n
    No 2 edges go between the same pair of vertices
    There are no self loops

Example Input:
4 5
1 2
1 3
2 3
3 4
1 4

Example Output:
2
3 4
1 4

This problem requires us to find a min cut of the graph. The min cut can be
found with a max-flow algorithm, such as Ford-Fulkerson. Once we find the max
flow, we can find which edges are in the min cut by running bfs on the residual
graph (which includes all edges where flow is less than capacity, including
residual edges). Mark every vertex reachable from the source as visited. Every
edge (u, v) where u is visited but v is not visited, that edge is a part of the
of the min cut of the graph.

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

        bool hasFlow() const {
            return capacity > 0 && flow > 0;
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
        if (u == sink || v == source || capacity == 0) return;
        edges.emplace_back(u, v, capacity);
        if (u == source || v == sink) {
            int e = (int) edges.size() - 1;
            graph[u].push_back(e);
        } else {
            edges.emplace_back(v, u, 0);
            int e = (int) edges.size() - 2;
            int r = (int) edges.size() - 1;
            edges[e].residualIndex = r;
            edges[r].residualIndex = e;
            graph[u].push_back(e);
            graph[v].push_back(r);
        }
    }

    long long maxFlow() {
        for (Edge& edge : edges) {
            edge.flow = 0;
        }
        long long totalFlow = 0;
        while (bfs()) {
            ++tok;
            while (true) {
                std::fill(next.begin(), next.end(), 0);
                long long pushed = dfs(source, 3e18);
                totalFlow += pushed;
                if (pushed == 0) break;
            }
        }
        return totalFlow;
    }

    std::vector<std::pair<int, int>> minCut() {
        maxFlow();
        std::vector<std::pair<int, int>> mc;
        for (const Edge& e : edges) {
            if (e.hasFlow() && visited[e.u] == tok && visited[e.v] != tok)
                mc.emplace_back(e.u + 1, e.v + 1);
        }
        return mc;
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
                    if (e.residualIndex != -1)
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

    int n, m;
    std::cin >> n >> m;
    MaxFlow flow(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        flow.addEdge(u, v, 1);
        flow.addEdge(v, u, 1);
    }
    auto minCut = flow.minCut();
    std::cout << minCut.size() << '\n';
    for (const auto& e : minCut) {
        std::cout << e.first << ' ' << e.second << '\n';
    }
}
