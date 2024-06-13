/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1397

For every farm i and query (v, s), Bessie is able to visit farm i if (c[i] -
t[i] > s). We can sort the farms by (c[i] - t[i]) and then, for each query,
perform binary search for the first index i where (c[i] - t[i] > s). Bessie
will be able to visit at least v farms if (n - i >= v).

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        c[i] -= x;
    }
    std::sort(c.begin(), c.end());
    while (q--) {
        int v, s;
        std::cin >> v >> s;
        auto vis = std::lower_bound(c.begin(), c.end(), s + 1);
        std::cout << (c.end() - vis >= v ? "YES" : "NO") << '\n';
    }
}
