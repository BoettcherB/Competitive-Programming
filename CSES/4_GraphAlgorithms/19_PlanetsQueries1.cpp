/*

CSES: Graph Algorithms: Planets Queries 1

You are given a directed graph with n vertices. Each vertex u has 1 outgoing
edge to a vertex v (u, v). You are also given q queries, each containing 2
integers x and k. For each query, find the vertex you would end up on if you
started at vertex x and travelled across k edges.

Constraints:
    1 <= n, q <= 200,000
    1 <= v <= n
    1 <= x <= n
    0 <= k <= 1,000,000,000

Example Input:
4 3
2 1 1 4
1 2
3 4
4 1

Example Output:
1
2
4

The graph in this problem is a functional graph, or a directed graph where each
vertex has 1 outgoing edge. We can use a technique called binary lifting to 
pre-compute the vertex we will end up on if we travel across 1 edge, 2 edges, 4
edges, 8 edges, etc. (all powers of 2). To find the result vertex if we want to
travel across k edges, we can find the msb (most significant bit) of k and 
travel across (1 << msb) edges in O(1) time. Then, remove the msb from k. Keep
doing this until k is 0.

Note: This problem has very tight time constraints. Normally, I would use
vectors: "std::vector<std::vector<int>> successor" but for this problem they 
are too slow. Instead I use C-style arrays: "int successor[200000][32]" because
they are faster.

*/

#include <iostream>

const int P = 32;
const int N = 2e5 + 10;
int successor[N][P];

int getMSB(int val) {
    return 31 - __builtin_clz(val);
}

int succ(int x, long long k) {
    long long val = k;
    while (val) {
        int bit = getMSB(val);
        x = successor[x][bit];
        val -= 1LL << bit;
    }
    return x;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> successor[i][0];
    }
    for (int p = 1; p < P; ++p) {
        for (int i = 1; i <= n; ++i) {
            successor[i][p] = successor[successor[i][p - 1]][p - 1];
        }
    }
    while (q--) {
        int x, k;
        std::cin >> x >> k;
        std::cout << succ(x, k) << '\n';
    }
}
