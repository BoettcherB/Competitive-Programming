/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1254

This problem can be solved using DP on trees. For each subtree rooted at node
i, store the number of haybales that this subtree needs. A positive value means
we need to bring in more haybales from outside the subtree (via the parent of
i, p_i) and a negative value means we need to pass some haybales out to p_i.

One solution is to run DFS twice on the tree, the first time passing haybales
upwards towards the root (gathering extra haybales from where they are not
needed) and then the second time passing haybales back down through the tree
(distributing them where needed). This works because when we gather extra
haybales there is guaranteed to be enough of them to carry out the order in
that instant. 
1)  For the first run of DFS we visit each child of i c_i first, gathering any
    extra haybales from the subtree rooted at c_i into c_i. Then we bring the
    extra haybales from c_i to i. Note that if c_i has extra haybales but c_j
    is lacking some, we will not pass any haybales from i to p_i. Instead, they
    will stay at i until the next run of dfs.
2)  For the second run of DFS, for each node i we determine if i has extra
    haybales that need to be distributed. If so, we distribute them to the
    children of i and then call dfs on each child.
Every time a pass of haybales is made, store the details of that pass somewhere
so they can all be printed at the end.

Another (probably much more intuitive) solution involves the realization that
we only need to pass haybales over an edge once. We will never have to pass
haybales from u to v, and then back from v to u, and we will never have to make
2 separate passes over edge (u,v). With this knowledge we can give each edge a
direction based on which way we need to pass haybales. This direction can be
determined using the same method above: using dfs to find out whether a subtree
needs haybales or has extra. Once we have a directed tree we can sort the nodes
in topological order. Then, for each node simply pass haybales down the list.

*/

#include <iostream>
#include <vector>

struct Order {
    int source, dest;
    long long amount;
    Order(int s, int d, long long a) : source{ s }, dest{ d }, amount{ a } {}
};

const int N = 2e5 + 10;
std::vector<std::vector<int>> tree(N);
std::vector<Order> orders;
long long goal, needs[N];

void distribute(int cur, int p) {
    for (int child : tree[cur]) {
        if (child == p)
            continue;
        if (needs[child] > 0)
            orders.emplace_back(cur, child, needs[child]);
        distribute(child, cur);
    }
}

void gather(int cur, int p) {
    for (int child : tree[cur]) {
        if (child == p)
            continue;
        gather(child, cur);
        if (needs[child] >= 0)
            needs[cur] += needs[child];
        else {
            long long extra = -needs[child];
            orders.emplace_back(child, cur, extra);
            needs[cur] -= extra;
            needs[child] = 0;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> needs[i];
        goal += needs[i];
    }
    goal /= n;
    for (int i = 1; i <= n; ++i) {
        needs[i] = goal - needs[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    gather(1, 0);
    distribute(1, 0);
    std::cout << orders.size() << '\n';
    for (const Order& o : orders) {
        std::cout << o.source << ' ' << o.dest << ' ' << o.amount << '\n';
    }
}
