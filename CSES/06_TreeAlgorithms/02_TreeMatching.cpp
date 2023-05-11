/*

Given a tree with n nodes as a list of edges, find the size of the largest
matching. A matching is a set of edges where each node is an endpoint of at
most 1 edge (i.e. a set of edges where no 2 edges are adjacent / share a node).

This problem can be solved using DP on trees. We can define dp[i][0] to be the
size of the largest matching of the subtree rooted at node i. Similarly, we can
define dp[i][1] to be the largest matching of the subtree rooted at node i, but
with a restriction: none of the edges in the matching can include node i (i.e.
node i cannot be an endpoint of any edge in the matching).

For any node i with children (c1, c2, ..., cj), dp[i][1] is just dp[c1][0] +
dp[c2][0] + ... + dp[cj][0]. The restriction on dp[i][1] prohibits us from
taking edge (i,c) (c is a child of i), so we do not have to worry about a
collision between edge (i,c) and any edge within the subtree rooted at c.

To find dp[i][0] we have to consider all edges (i,c). If we take edge (i,c1) we
can no longer use dp[c1][0] because there could be a collision between (i,c1)
and an edge within the subtree of c1. Instead we can use dp[c1][1] because the
restriction prevents a collision of this kind. If we take edge (i,c1), dp[i][0]
will be dp[i][1] - dp[c1][0] + dp[c1][1] + 1. To find dp[i][0], perform this
operation on all the children on i and take the maximum result.

Recurrence:
 - dp[i][0] = dp[i][1] + max(dp[c][1] - dp[c][0] + 1) for all children c of i
 - dp[i][1] = SUM(dp[c][0]) for all children c of i

We can use dfs to find the values of dp[][] for the children of i before
calculating the values for i. For any leaf node L, dp[L][0] = dp[L][1] = 0.

Constraints:
 - 1 <= n <= 200,000
 - 1 <= a, b <= n (for each given edge (a, b))
 - The given edges make a single tree

Example Input:
5
1 2
1 3
3 4
3 5

Example Output:
2

*/

#include <iostream>
#include <vector>

const int N = 2e5 + 10;
std::vector<std::vector<int>> tree(N);
int dp[N][2];

void dfs(int cur, int p) {
    for (int child : tree[cur]) {
        if (child == p) continue;
        dfs(child, cur);
        dp[cur][1] += dp[child][0];
    }
    for (int child : tree[cur]) {
        if (child == p) continue;
        dp[cur][0] = std::max(dp[cur][0], 1 - dp[child][0] + dp[child][1]);
    }
    dp[cur][0] += dp[cur][1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int u, v;
        std::cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, 0);
    std::cout << dp[1][0] << std::endl;
}
