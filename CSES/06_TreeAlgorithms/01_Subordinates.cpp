/*

Given a tree of n nodes (1..n) rooted at node 1, find the number of descendents
of each node. We are given a list of n-1 integers: the parent of nodes (2..n).
Print n integers: the total number of descendents for nodes (1..n).

Constraints:
 - 1 <= n <= 200,000
 - The input forms a single tree

Example Input:
5
1 1 2 3

Example Output:
4 1 1 0 0

This problem can be solved by using dfs to find the total subtree size for each
node. Then, the total number of descendents for node i is subtree_size[i] - 1.

*/

#include <iostream>
#include <vector>

const int N = 2e5 + 10;
std::vector<std::vector<int>> tree(N);
int subtree_size[N];

void dfs(int cur) {
    subtree_size[cur] = 1;
    for (int child : tree[cur]) {
        dfs(child);
        subtree_size[cur] += subtree_size[child];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        int v;
        std::cin >> v;
        tree[v].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        std::cout << (subtree_size[i] - 1) << ' ';
    }
    std::cout << std::endl;
}
