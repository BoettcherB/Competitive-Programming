/*

Problem Statement: https://atcoder.jp/contests/abc355/tasks/abc355_e

For this problem, we are allowed to query specific ranges [l, r) in order to
find the sum of a target range [L, R). A good way to solve this is to think of
each number as a vertex on a graph. If we start at vertex u and there is a
range [u, v), then we can think of there being an edge between u and v. This
edge means that we can find out the sum of [u, v) in one query. To find the
sum of the range [L, R) in the fewest number of queries, we need to find the
shortest path from L to R in the graph, which can be done with bfs.

Note that we might go outside of the range [L, R). For example, the fewest
number of queries might be 2: [L, R + 2) and [R, R + 2). In this case, we need
to subtract [R, R + 2) from [L, R + 2) because that range was counted twice.

*/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

const int MOD = 100;

int ask(int l, int r) {
    bool neg = l > r;
    if (neg) std::swap(l, r);
    int i = (int) std::log2(r - l);
    int j = l / (1 << i);
    std::cout << "? " << i << ' ' << j << std::endl;
    int res;
    std::cin >> res;
    return neg ? -res : res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, l, r;
    std::cin >> n >> l >> r;
    int lim = 1 << n;
    std::vector<std::vector<int>> g(lim + 1);
    for (int i = 0; i <= n; ++i) {
        int p = 1 << i;
        for (int j = 0; p * (j + 1) <= lim; ++j) {
            g[p * j].push_back(p * (j + 1));
            g[p * (j + 1)].push_back(p * j);
        }
    }
    std::vector<int> from(lim + 1, -1);
    std::queue<int> q;
    q.push(l);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (from[v] == -1) {
                from[v] = u;
                q.push(v);
            }
        }
    }
    int res = 0, v = r + 1;
    while (v != l) {
        int u = from[v];
        res += ask(u, v);
        v = u;
    }
    std::cout << "! " << ((res % MOD + MOD) % MOD) << std::endl;
}
