/*

Problem Statement: https://atcoder.jp/contests/abc355/tasks/abc355_f

For this problem, the key is that each edge weight can only be 1 <= w <= 10.
With this information, we can set up 10 dsu data structures where dsu[i] is
made up of only edges with weight <= i. Whenever we add an edge with weight w
between u and v, we can find the maximum edge on the path from u to v by
searching our 10 dsu structures and finding the first one where u and v are
not in the same component. For example, if u and v are in the same component in
dsu[5] but not in dsu[4], then the maximum edge on the path from u to v is 5.
Then, if we want to add an edge between u and v of weight 2, we need to update
dsu[2], dsu[3], and dsu[4] to have u and v in the same component. After this
operation, the total sum of the MST decreases by 5 - 2 = 3. Note that we do not
need to do anything to "remove" edges since we are detecting edges by comparing
the different dsu's.

*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> vvec;
vvec parent, size;

int find(int v, int w) {
    return v == parent[v][w] ? v : parent[v][w] = find(parent[v][w], w);
}

bool merge(int a, int b, int w) {
    if ((a = find(a, w)) != (b = find(b, w))) {
        if (size[a][w] < size[b][w]) std::swap(a, b);
        parent[b][w] = a;
        size[a][w] += size[b][w];
        return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    parent = size = vvec(n + 1, std::vector<int>(11));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 10; ++j) {
            parent[i][j] = i;
            size[i][j] = 1;
        }
    }
    int sum = 0;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        sum += w;
        for (int j = w; j <= 10; ++j) {
            merge(u, v, j);
        }
    }
    while (q--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        int found = 0;
        for (int j = w; j <= 10; ++j) {
            if (!merge(u, v, j)) {
                found = j;
                break;
            }
        }
        sum -= found - w;
        std::cout << sum << '\n';
    }
}
