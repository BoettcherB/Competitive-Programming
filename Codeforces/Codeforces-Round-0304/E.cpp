/*

Problem Statement: https://codeforces.com/contest/546/problem/E

This problem can be solved using a max-flow algorithm. Create 2 'layers' of
nodes, each with all n vertices of the given graph, as well as a source and
sink node. Connect the source node to all nodes in layer 1 with the capacity of
the edge to node i equal to a[i], and connect all nodes in layer 2 to the sink
with the capacity of the edge from node i equal to b[i]. Then, add 2 edges from
layer 1 to layer 2 for each undirected edge in the input graph: one from (u, v)
and one from (v, u), each with infinite capacity. Also, add an edge (u, u) for
all vertices u with infinite capacity (flow across these edges represents
soldiers that do not move across an edge). If the sum of a[i] for all i does
not equal the sum of b[i] for all i, or if the sum of a[i] does not equal the
max flow through the flow graph, then there is no solution. If there is a
solution, loop through each edge (flow layer 1 to layer 2) in the flow graph
and add its flow to a matrix.

It can be tricky to recognize problems as flow problems. I did not notice that
this was a flow problem at first. My advice is to look for problems asking us
to transfer items between nodes, or problems involving balancing input and
output at each node.

*/

#include <iostream>
#include <vector>
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
        if (capacity == 0) return;
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
                if (pushed == 0) break;
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
    
public:
    std::vector<std::vector<int>> getEdges(int n) {
        std::vector<std::vector<int>> weights(n, std::vector<int>(n));
        for (const Edge& edge : edges) {
            if (edge.capacity != 0 && edge.u != source && edge.v != sink) {
                weights[edge.u][edge.v - n] = (int) edge.flow;
            }
        }
        return weights;
    }
};

const int INF = 2e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    int source = 2 * n, sink = 2 * n + 1;
    MaxFlow flow(2 * n + 2, source, sink);
    long long sumA = 0, sumB = 0;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sumA += a[i];
        flow.addEdge(source, i, a[i]);
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
        sumB += b[i];
        flow.addEdge(n + i, sink, b[i]);
        flow.addEdge(i, n + i, INF);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        flow.addEdge(u, n + v, INF);
        flow.addEdge(v, n + u, INF);
    }
    if (sumA != sumB || flow.maxFlow() != sumA)
        std::cout << "NO" << '\n';
    else {
        std::cout << "YES" << '\n';
        std::vector<std::vector<int>> edgeWeights = flow.getEdges(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << edgeWeights[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
}
