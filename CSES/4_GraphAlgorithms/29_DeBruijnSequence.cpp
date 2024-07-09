/*

CSES: Graph Algorithms: De Bruijn Sequence

Your task is to create a minimum-length bit string that contains all possible
substrings of length n. For example, when n = 2, the substrings of length 2 are
00, 01, 10, and 11

Constraints:
    1 <= n <= 15

Example Input:
2

Example Output:
00110

This problem can be solved by creating a De Buijn Graph and finding an Euler
Circuit of the graph. A De Bruijn Graph for a length n string has 2^(n-1)
vertices: one for each substring of length n-1. Then, each vertex has 2
outgoing edges. The first is labeled '0' and its destination is the substring
we will get if we add '0' to the beginning of the substring and remove the last
character. The second is labeled '1' and its destination is the substring we
will get if we add '1' to the front and remove the last character. For example,
the substring '10011' has an edge to '01001' and '11001'. Note that this is one
way to create a De Bruijn Graph. We could also remove the first character and 
add the new charcter to the end to get the destination vertex.

To find a De Bruijn Sequence, we start at any vertex and traverse across an
Euler Circuit of the graph. The sequence will be the substring at the starting
vertex plus all the labels of the edges, in order.

*/

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::vector<int>> Graph;

std::string sequence;

void dfs(int u, Graph& g) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        sequence.push_back((u >> 1) == v ? '0' : '1');
        dfs(v, g);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << "01" << '\n';
        return 0;
    }
    int numVerts = 1 << (n - 1);
    Graph g(numVerts);
    for (int i = 0; i < numVerts; ++i) {
        g[i].push_back(i >> 1);
        g[i].push_back((i >> 1) | (1 << (n - 2)));
    }
    sequence = std::string(n - 1, '0');
    dfs(0, g);
    std::cout << sequence << '\n';
}
