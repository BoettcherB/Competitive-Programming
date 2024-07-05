/*

CSES: Graph Algorithms: Road Construction

You are given an undirected graph with n vertices and m edges. Initially there
are 0 edges but they are added 1 by 1. After each edge is added to the graph,
determine the number of components in the graph and the size of the largest
component.

Constraints:
    1 <= n <= 100,000
    1 <= m <= 200,000
    1 <= u, v <= n
    There are no self loops

Example Input:
5 3
1 2
1 3
4 5

Example Output:
4 2
3 3
2 3

This problem can be solved using a DSU data structure. Initially there are n
components, but after each merge the number of components decreases by 1. The
size of the largest component can also only increase during a merge.

*/

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> parent, size;
int comps, largest = 1;

int find(int v) {
    return v == parent[v] ? v : parent[v] = find(parent[v]);
}

void merge(int a, int b) {
    if ((a = find(a)) != (b = find(b))) {
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        largest = std::max(size[a], largest);
        --comps;
    }
}

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const {
        return w < o.w;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    comps = n;
    parent = size = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        size[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        merge(u, v);
        std::cout << comps << ' ' << largest << '\n';
    }
}
